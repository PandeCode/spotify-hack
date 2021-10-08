#pragma once
#include "crow/app.h"

enum class WaitMessage : std::uint8_t;

class Server {

	static const char* const s_socketHelp;
	static const char* const s_httpHelp;

	std::atomic_bool httpLocked;

	std::unordered_map<std::variant<crow::response*, crow::websocket::connection*>, WaitMessage>
	    waitingList;

	crow::SimpleApp m_app;
	uint16_t        m_port;
	crow::LogLevel  m_logLevel;

	std::vector<crow::websocket::connection*> m_clients;
	std::atomic<crow::websocket::connection*> playerClient = nullptr;

	void addWaitingList(const std::variant<crow::response*, crow::websocket::connection*>&, WaitMessage);
	void removeWaitingList(const std::variant<crow::response*, crow::websocket::connection*>&);

	void checkGiveClient(const WaitMessage dataType, const std::string& data);

	void waitForEnterKey();

	void sendToAllClients(const char* text);
	void sendToPlayerClient(const char* text);

	void enableAllEndpoints();
	void enableClientWebsocket();
	void enablePlayerClientWebsocket();
	void enableHelpEndpoints();
	void enableHttpClient();
	void enableHtmlClient();

      public:
	Server(
	    const uint16_t&       port     = 8080,
	    const crow::LogLevel& logLevel = crow::LogLevel::Info);

	Server()              = delete;
	Server(const Server&) = delete;
	~Server();

	void startServer();
	void killServer();
};
