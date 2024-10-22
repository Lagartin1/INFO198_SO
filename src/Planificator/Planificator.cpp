#include "../include/Planificador.h"
void sendMessageToDistrubuter(int core_id,string& operacion,string& num1,string& num2);
void scheduler(vector<Core> &cores, string procesosPath);


int main() {
    //ejecucion del distribuidor para usar sockets
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Error al crear el proceso hijo" << endl;
        exit(EXIT_FAILURE);
    }else if(pid == 0 ){
        execl("./distribuidor","distribuidor",nullptr);
        perror("Error al ejecutar el distribuidor");

    }else {
        cout << "Iniciando Planificador" << endl;
        sleep(3); //espera para que se inicie el distribuidor
        string procesosPath = getenv("PROCESOS");
        string resultadosPath = getenv("RESULTADOS");
        string cantCores = getenv("CANTIDAD_CORES");
        int nCores = stoi(cantCores);
        vector<Core> cores_list(nCores);
        for (int i = 0; i < nCores; i++) {
            avalible_cores.push(i);
        }
        thread schedThread(scheduler, ref(cores_list), procesosPath);
        schedThread.join();
        //waitpid(pid, nullptr, 0);
        cout << "Planificador finalizado" << endl;
        cout << "Los resultados se encuentran en: "<< resultadosPath << endl;
    } 
    return 0;
}

void scheduler(vector<Core> &cores, string procesosPath){
    ifstream file(procesosPath);
    string lines;
    while (getline(file, lines)){
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, []{return !avalible_cores.empty();}); // Esperar a que haya un core disponible

        int core_id = avalible_cores.front();
        avalible_cores.pop();
        lck.unlock();
        stringstream line(lines);
        string n,operaction, n1,n2;
        getline(line, n, ';');
        getline(line, operaction, ';');
        getline(line, n1, ',');
        getline(line, n2, ';');
        //
        sendMessageToDistrubuter(core_id,operaction,n1,n2);
        //
        lck.lock();
        avalible_cores.push(core_id);
        cv.notify_one();  // Notificar que hay un core disponible
        lck.unlock();
    }
     // Esperar a que todos los threads terminen
    for (auto& core : cores) {
        if (core.worker.joinable()) {
            core.worker.join();
        }
    }
    file.close();
}



void sendMessageToDistrubuter(int core_id,string& operacion,string& num1,string& num2){
    int socket_fd;
    struct sockaddr_un server_addr;
    // Crear un socket Unix
    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("Error al crear el socket");
        return;
    }
    // Configurar la dirección del socket
    server_addr.sun_family = AF_UNIX;
    string socket_dir = getenv("SOCKET_DIR");
    socket_dir += "/sDistrib";
    strcpy(server_addr.sun_path, socket_dir.c_str());

    // Conectar al socket del distribuidor
    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al conectar al distribuidor");
        close(socket_fd);
        return;
    }
    // Enviar la operación al distribuidor
    stringstream ss;
    ss << core_id << ";" << operacion << ";" << num1 << "," << num2<<";";
    string operacion_str = ss.str();
    send(socket_fd, operacion_str.c_str(), operacion_str.size(), 0);
    // Cerrar el socket
    close(socket_fd);

}