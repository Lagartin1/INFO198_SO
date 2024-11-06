#include "../../include/SearchCache.h"

void reemplazarMasAntiguo(vector<Pbusqueda>& cache,string& nuevaPalabra,string& nuevoContenido) {
    auto masAntiguo = cache.begin();
    for (auto it = cache.begin(); it != cache.end(); ++it) {
        if (it->getIngreso() < masAntiguo->getIngreso()) {
            masAntiguo = it;
        }
    }
    // Reemplazar el elemento más antiguo
    masAntiguo->setPalabra(nuevaPalabra);
    masAntiguo->setContenido(nuevoContenido);
    masAntiguo->setIngreso(system_clock::now());

}
void agregarCache(vector<Pbusqueda>& cache,string& palabra,string& contenido){
    cache.push_back(Pbusqueda(palabra, contenido, system_clock::now()));
}


string searchCache(vector<Pbusqueda> &cache,string palabra,int size){
    string respuesta;
    int tam = cache.size();
    if (tam > 0 && tam <= size){
        if (tam == size){
            //llamar a motor de busqueda y  a cache
            for (int i = 0; i < size; i++){
                if (cache[i].getPalabra() == palabra){
                    return cache[i].getContenido();
                }
            }
            respuesta = sendMessageToEngine(palabra);
            reemplazarMasAntiguo(cache,palabra,respuesta);
        }else{
            //llamar a motor de busqueda y añadir a cache
            respuesta = sendMessageToEngine(palabra);
            agregarCache(cache,palabra,respuesta);
            //enviar respuesta a buscador
        }
    }else{
        respuesta = sendMessageToEngine(palabra);
        agregarCache(cache,palabra,respuesta);
    }
    return respuesta;
}



string sendMessageToEngine(string palabra){
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2021);  // Puerto del motor
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al conectar con el motor de búsqueda");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    send(socket_fd, palabra.c_str(), palabra.size(), 0);
    char buffer[1024];
    int bytes_received = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
        perror("Error al recibir la palabra");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_received] = '\0';
    close(socket_fd);
    return buffer;

}



int main() {
    string sSize = getenv("MEMORY_SIZE");
    int size = stoi(sSize);
    vector<Pbusqueda> cache;
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Error al crear el proceso hijo" << endl;
        exit(EXIT_FAILURE);
    }else if(pid == 0 ){
        execl("./engine","Motor De busqueda",nullptr);
        perror("Error al ejecutar el Motor de busqueda");

    }else {
        sleep(1);
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            perror("Error al crear el socket");
            exit(EXIT_FAILURE);
        }

        int opt = 1;
        if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
            perror("Error al configurar SO_REUSEADDR y SO_REUSEPORT en Cache");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2020);  // Usando el puerto 2020 para el caché
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            perror("Error en bind cache");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        if (listen(socket_fd, 1) == -1) {
            perror("Error en listen cache");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
        while (true) {
            // Aceptar conexión del cliente (buscador)
            int client_fd = accept(socket_fd, nullptr, nullptr);
            if (client_fd == -1) {

                perror("Error en accept en cache");
                sleep(1000000);
                continue;
            }
            // Recibir la operación del planificador
            char buffer[1024];
            int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received == -1) {
                perror("Error al recibir la palabra");
                close(socket_fd);
                continue;
            }
            buffer[bytes_received] = '\0';
            string palabra = buffer;
            string rsp;
            if (palabra == "!!") {
                //llamar a motor de busqueda para que termine mensaje será (!!)
                sendMessageToEngine("!!");
                send(client_fd, "success", 7, 0);
                close(socket_fd);
                exit(EXIT_SUCCESS);
                //terminar
            }
            
            rsp = searchCache(cache,palabra,size);
            send(client_fd, rsp.c_str(), rsp.size(), 0);
            close(client_fd);
        }

        close(socket_fd);
    }
}

