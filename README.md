# Linux Chat Program
## Client
### Compiling in QT
1) Clone the repo
2) Open client project in QT
3) Ensure build directory is the same as the client source code
4) Build the project

### Running from QT
1) After Compiling, run the application and it should compile and run

### Running from terminal (Requires QT libraries installed)
1) Open terminal window and navigate to the build directory
2) run command $./Comp4981ChatProgram
3) Application should open and run

### Using Client
1) After client window has opened, type in the servers IP address and port used into their relevent fields
2) Type in your username in the username field
3) Click the connect button to establish a connection to the server
4) If connection was successful, ----Connected---- will appear in the chat window
5) As additional clients connect, it will display their usernames in the users display window
6) To send messages to other clients/users, type a message into the message box and either click the Send button or hit the Enter key on your keyboard.

## Server
### Compiling
1) Clone the repo
2) Open the terminal window and navigate to the source file directory of the server
3) run the command $make

### Running the server
1) From the server source directory run the command $./chat_server
2) Server should start and wait for client connections
3) Server will update when new clients are connected and display their IP address and username
