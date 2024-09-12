#include "../include/UsersTools.h"
#include "../include/TextTools.h"

void extractUsers(map <string,Usuario> &users) {
    const char* txtFilePath = getenv("TXT_FILE_PATH");

    if (txtFilePath == nullptr) {
        cout << "Error: la variable de entorno TXT_FILE_PATH no está configurada." << endl;
        cout << "Configure la variable de entorno TXT_FILE_PATH con la ruta del archivo csv, de la forma especificada en el archvio README.md" << endl;
        exit(EXIT_FAILURE);
    }
    ifstream file(txtFilePath);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo" << std::endl;
        cout << "Verifique que existe el archivo Users.csv y que la variable de entorno CSV_FILE_PATH este correctamente configurada" << endl;
        exit(EXIT_FAILURE);
    }
    string lines;
    while (getline(file, lines)) {
        // lineas de la forma user;pass
        stringstream line(lines);
        string user, pass,tipo;
        getline(line, user, ';');
        getline(line, pass, ';');
        getline(line, tipo, ';');
        users[user] = Usuario(user, pass, tipo);
    }
    file.close();
}

void verificarUsuario(string user, string pass){
    // Usuario con menos de 3 letras
    if (user.length() <= 3) {
        cout << "Error: El usuario debe tener al menos 3 letras" << endl;
        exit(EXIT_FAILURE); 
    }
    // pass con menos de 6 caracteres
    if (pass.length() < 6) {
        cout << "Error: Usuario o contraseña incorrectos" << endl;
        exit(EXIT_FAILURE); 
    }
    // usuario contiene numeros
    for (char c : user) {
        if (isdigit(c)) {
            cout << "Error: El usuario no puede contener números" << endl;
            exit(EXIT_FAILURE);
        }
    }
    // pass contiene caracteres que no son letras ni números
    for (char c : pass) {
        if (!isalnum(c)) {
            cout << "Error: Usuario o contraseña incorrectos" << endl;
            exit(EXIT_FAILURE); 
        }
    }
}

void listUsers(map <string,Usuario> &users){
    cout << "=========================================="<<endl;
    cout << "           Lista de usuarios" << endl;
    cout << "==========================================" << endl;
    for (auto const& x : users){
        cout << "Usuario: " << x.first << " Rol: "<<users[x.first].getTipo() << endl;
    }
}


bool verificarUsuarioNuevo(string user){
    // Usuario con menos de 3 letras
    if (user.length() < 3) {
        cout << "Error: El usuario debe tener al menos 3 letras" << endl;
        return false;
    }
    // usuario contiene numeros
    for (char c : user) {
        if (isdigit(c)) {
            cout << "Error: El usuario no puede contener números" << endl;
            return false;
        }
    }
    return true;
}

bool verficarPassUsuarioNuevo(string pass){
    // pass con menos de 6 caracteres
    if (pass.length() < 6) {
        cout << "Error: La contraseña debe tener almenos 6 caracteres" << endl;
        return false; 
    }
    // pass contiene caracteres que no son letras ni números   
    for (char c : pass) {
        if (!isalnum(c)) {
            cout << "Error: La contraseña solo puede contener letras y/o numeros" << endl;
            return false; 
        }
    }
    return true;
}

void addUserData(string user, string pass, string tipo){
    //agregar a archivo 
    ofstream file(getenv("TXT_FILE_PATH"), ios::app);
    file << user << ";" << pass << ";" << tipo << endl;
    file.close();
}


void addUser(map <string,Usuario> &users){
    string user, pass,pass2 ,tipo;
    char eleccion;
    cout << "Ingrese el nombre de usuario: ";
    getline(cin, user);
    while (! verificarUsuarioNuevo(user)){
        cout << "Ingrese el nombre de usuario: ";
        getline(cin, user);
    }
    cout << "Ingrese la contraseña: ";
    getline(cin, pass);
    while (! verficarPassUsuarioNuevo(pass)){
        cout << "Ingrese la contraseña: ";
        getline(cin, pass);
    }
    cout << "Ingrese nuevamente la contraseña: ";
    getline(cin, pass2);
    while ( (verficarPassUsuarioNuevo(pass2) && (pass != pass2)) ){
        cout << "Las contraseñas no coinciden" << endl;
        cout << "Ingrese la contraseña: ";
        getline(cin, pass);
        while (! verficarPassUsuarioNuevo(pass)){
            cout << "Ingrese la contraseña: ";
            getline(cin, pass);
        }
        cout << "Ingrese nuevamente la contraseña: ";
        getline(cin, pass2);
    }

    cout << "Ingrese el tipo de usuario(Admin(A) / Generico(G) ): ";
    cin >> eleccion;
    while ( tolower(eleccion) != 'a' && tolower(eleccion)  != 'g') {
        cout << "Ingrese el tipo de usuario(Admin(A) / Generico(G) ): ";
        cin >> eleccion;
    }
    cin.ignore();  // Ignorar el salto de línea para el proximo cin
    if( tolower(eleccion) == 'a'){
        tipo = "Admin";
    }else{
        tipo = "Usuario Generico";
    }
    users[user] = Usuario(user, pass, tipo);
    //agregar a archivo 
    addUserData(user, pass, tipo);
    cout << "Usuario agregado exitosamente" << endl;
}

bool deleteUserData(string user){
    // Obtener la ruta del archivo de texto desde la variable de entorno
    const char* filePath = getenv("TXT_FILE_PATH");
    // Abrir el archivo original y un archivo temporal
    ifstream file(filePath);
    ofstream temp("temp.txt");
    if (!temp.is_open()) {
        cerr << "Error: No se pudo abrir el archivo temporal." << endl;
        file.close();
        return false;
    }
    string line;
    while (getline(file, line)) {
        stringstream lineStream(line); 
        string userFile;
        getline(lineStream, userFile, ';');  // Leer hasta el primer ';'
        // Si el nombre de usuario no coincide, escribir la línea en el archivo temporal
        if (userFile != user) {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();
    // Reemplazar el archivo original con el archivo temporal
    if (rename("temp.txt",filePath) != 0) {
        cerr << "Error: No se pudo eliminar el archivo original." << endl;
        return false;
    }
    return true;
}


void deleteUser(map <string,Usuario> &users){
    string user;
    while (true){
        cout << "Ingrese el nombre de usuario a eliminar (L: para listar usuarios): ";
        getline(cin, user);
        if ( user.length() == 1 && tolower(user[0]) == 'l'){
            listUsers(users);
            cout << "Ingrese el nombre de usuario a eliminar (L: para listar usuarios): ";
            getline(cin, user);
        }
        if (users.find(user) != users.end()){
            if(users[user].getTipo() == "Admin"){
                cout << "\nError: No se puede eliminar un usuario administrador" << endl;
                return;
            }else{
            users.erase(user);
            //actualizar archivo
            if (!deleteUserData(user)) {
                cout << "Error: No se pudo eliminar el usuario" << endl;
                return;
            }else{
                cout << "Usuario eliminado exitosamente" << endl;
                return;
            }
            }
            
        }else{
            borrarConsola();
            cout << "Error: El usuario '"<< user << "' no existe" << endl;
        }
    }
}

