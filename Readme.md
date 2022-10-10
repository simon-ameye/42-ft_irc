# TODO
- envoyer le bon code pour la loste des users dans JOIN : RPL_NAMREPLY
- rendre le passProvided obligatoire dans toutes les fonctions
- rendre les classes private
- verifier la presence de tous les retours et erreurs dans chaque fonction

# ft-irc
An IRC server
## Graph :

```mermaid
flowchart TD
    subgraph server::init
        direction TB
        socket["create master socket"]
        setsockopt
        bind
        listen
        socket-->setsockopt-->bind-->listen
        end
    subgraph server::loop
        direction TB
        subgraph server::connect
            direction TB
            pollfds[create pollfds vector and put master and clients sockets inside]
            poll["poll: monitor pollfds (BLOCKING)"]
            newClient["client::new() : add new client in server::clients"]
            accept["clientSocket = accept(master socket)"]
            newClient-->accept
            pollfds-->poll
            poll-->|"if FD_ISSET(master socket)==1"|newClient
            poll-->|"else"|pass
            end
        subgraph server::getMessages
            direction TB
            checkClients["FD_ISSET on each client socket"]
            recv["recv on client buffer"]
            concat["concat recv buffer to client buffer"]
            close_socket["\0 in client buffer, close socket ?"]
            checkClients-->|"if FD_ISSET==1"|recv
            recv-->|"recv return > 0"|concat
            recv-->|"recv buffer == 0"|close_socket
            direction TB
            end
        subgraph server::dispatchs
            direction TB
            checkinput["check all client _inputMessagesBuffer ending with \0 meaning it's ready"]
            process["process: Channels::doTheStuff to fill _outputMessage"]
            reset["resset _inputMessagesBuffers to \0"]
            checkinput-->process-->reset
            end
        subgraph server::sendMessage
            direction TB
            checkoutput["check all client _outputMessage"]
            send["send(socket , buffer)"]
            checkoutput-->send
            end
        end
    server::init-->server::connect-->server::getMessages-->server::dispatchs-->server::sendMessage
```

## Classes :

```mermaid
classDiagram
    class Server{
        +Server(server settings)
        ~Server()
        -socket masterSocket
        -vector~Client~ clients
        -vector~Channel~ channels
        +init()
        +connect()
        +getMessages()
        sockaddr_in _sin;
        socklen_t _sizeofsin;
    }
    class Client{
        ~Client()
        +Client(client settings)
        +getClientSocket()
        +getInputBuffer()
        +getOutputBuffer()
        -socket clientSocket
        -char _inputMessagesBuffer[42]
        -char _outputMessage[42]
    }
    class Channel{
        +Channel(channel settings)
        ~Channel()
        -std::string name
        +getName()
        -...
    }

Server <-- Client
Server <-- Channel
```