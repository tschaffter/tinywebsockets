#pragma once

#include <tiny_websockets/internals/ws_common.hpp>
#include <tiny_websockets/network/tcp_client.hpp>
#include <tiny_websockets/internals/data_frame.hpp>
#include <tiny_websockets/internals/websockets_endpoint.hpp>
#include <tiny_websockets/message.hpp>
#include <functional>

namespace websockets {
	enum class WebsocketsEvent {
		ConnectionOpened,
		ConnectionClosed,
		GotPing, GotPong
	};
    typedef std::function<void(WebsocketsMessage)> MessageCallback;
    typedef std::function<void(WebsocketsEvent, WSInterfaceString data)> EventCallback;

	class WebsocketsClient : private internals::WebsocketsEndpoint {
	public:
		WebsocketsClient();

		bool connect(WSInterfaceString url);
		bool connect(WSInterfaceString host, int port, WSString path);
		
		void onMessage(MessageCallback callback);
		void onEvent(EventCallback callback);

		bool poll();
		bool available(bool activeTest = false);

		bool send(WSInterfaceString data);
		bool send(char* data, size_t len);
		bool sendBinary(WSInterfaceString data);
		bool sendBinary(uint8_t* data, size_t len);
		
		WebsocketsMessage readBlocking();

		bool ping(WSInterfaceString data = "");
		bool pong(WSInterfaceString data = "");

		void close();

	private:
		WSDefaultTcpClient _client;
		bool _connectionOpen;
		MessageCallback _messagesCallback;
		EventCallback _eventsCallback;

		void _handlePing(WebsocketsMessage);
		void _handlePong(WebsocketsMessage);
		void _handleClose(WebsocketsMessage);
	};
}