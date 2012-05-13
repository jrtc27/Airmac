//
// This file is part of Airmac.
//
// This version of Airmac is a continuation of Airmac version 0.4
// developed by Arend Jan Kramer, which was available at the time of
// writing from <http://code.google.com/p/airmac/>.
//
// Airmac is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Airmac is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Airmac.  If not, see <http://www.gnu.org/licenses/>.
//

#import "TCPServer.h"

@protocol AirplayDelegate;

@protocol AirplayDelegate <NSObject>
@optional
@end


@class HTTPConnection, HTTPServerRequest;

@interface HTTPServer : TCPServer {
@private
    Class connClass;
    NSURL *docRoot;
	id <AirplayDelegate> airplaydelegate;

}

- (Class)connectionClass;
- (void)setConnectionClass:(Class)value;
// used to configure the subclass of HTTPConnection to create when  
// a new connection comes in; by default, this is HTTPConnection

- (id)airplaydelegate;
- (void)setAirplayDelegate:(id)value;

@end

@interface HTTPServer (HTTPServerDelegateMethods)
- (void)HTTPServer:(HTTPServer *)serv didMakeNewConnection:(HTTPConnection *)conn;
// If the delegate implements this method, this is called  
// by an HTTPServer when a new connection comes in.  If the
// delegate wishes to refuse the connection, then it should
// invalidate the connection object from within this method.
@end


// This class represents each incoming client connection.
@interface HTTPConnection : NSObject <NSStreamDelegate> {
@private
    id delegate;
    NSData *peerAddress;
    HTTPServer *server;
    NSMutableArray *requests;
    NSInputStream *istream;
    NSOutputStream *ostream;
    NSMutableData *ibuffer;
    NSMutableData *obuffer;
    BOOL isValid;
    BOOL firstResponseDone;
	float _playPosition;
	float _playDuration;
	float _playRate;
	
	BOOL hasReversed;
}

@property (nonatomic, assign) id <AirplayDelegate> airplaydelegate;

- (id)initWithPeerAddress:(NSData *)addr inputStream:(NSInputStream *)istr outputStream:(NSOutputStream *)ostr forServer:(HTTPServer *)serv;

- (id)delegate;
- (void)setDelegate:(id)value;


- (NSData *)peerAddress;

- (HTTPServer *)server;

- (HTTPServerRequest *)nextRequest;
// get the next request that needs to be responded to

- (BOOL)isValid;
- (void)invalidate;
// shut down the connection

- (void)performDefaultRequestHandling:(HTTPServerRequest *)sreq;
// perform the default handling action: GET and HEAD requests for files
// in the local file system (relative to the documentRoot of the server)

@end

@interface HTTPConnection (HTTPConnectionDelegateMethods)
- (void)HTTPConnection:(HTTPConnection *)conn didReceiveRequest:(HTTPServerRequest *)mess;
- (void)HTTPConnection:(HTTPConnection *)conn didSendResponse:(HTTPServerRequest *)mess;

- (void)videoSent:(NSString*)url startPosition:(float)start;
- (void)videoClosed;
- (void)videoDidPauseOrPlay:(BOOL)pause;
- (void)videoDidScrubTo:(float)seconds;
- (void)photoSent:(NSData*)photoData;

- (float)airplayDidAskPosition;
- (float)airplayDidAskDuration;
- (float)airplayDidAskRate;

// The "didReceiveRequest:" is the most interesting -- 
// tells the delegate when a new request comes in.
@end


// As NSURLRequest and NSURLResponse are not entirely suitable for use from 
// the point of view of an HTTP server, we use CFHTTPMessageRef to encapsulate
// requests and responses.  This class packages the (future) response with a
// request and other info for convenience.
@interface HTTPServerRequest : NSObject {
@private
    HTTPConnection *connection;
    CFHTTPMessageRef request;
    CFHTTPMessageRef response;
    NSInputStream *responseStream;
}

- (id)initWithRequest:(CFHTTPMessageRef)req connection:(HTTPConnection *)conn;

- (HTTPConnection *)connection;

- (CFHTTPMessageRef)request;

- (CFHTTPMessageRef)response;
- (void)setResponse:(CFHTTPMessageRef)value;
// The response may include a body.  As soon as the response is set, 
// the response may be written out to the network.

- (NSInputStream *)responseBodyStream;
- (void)setResponseBodyStream:(NSInputStream *)value;
// If there is to be a response body stream (when, say, a big
// file is to be returned, rather than reading the whole thing
// into memory), then it must be set on the request BEFORE the
// response [headers] itself.

@end

