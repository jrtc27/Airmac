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

#import <Foundation/Foundation.h>
#import <CoreServices/CoreServices.h>

NSString * const TCPServerErrorDomain;

typedef enum {
    kTCPServerCouldNotBindToIPv4Address = 1,
    kTCPServerCouldNotBindToIPv6Address = 2,
    kTCPServerNoSocketsAvailable = 3,
} TCPServerErrorCode;

@interface TCPServer : NSObject <NSNetServiceDelegate> {
@private
    id delegate;
    NSString *domain;
    NSString *name;
    NSString *type;
    uint16_t port;
    CFSocketRef ipv4socket;
    CFSocketRef ipv6socket;
    NSNetService *netService;
}

- (id)delegate;
- (void)setDelegate:(id)value;

- (NSString *)domain;
- (void)setDomain:(NSString *)value;

- (NSString *)name;
- (void)setName:(NSString *)value;

- (NSString *)type;
- (void)setType:(NSString *)value;

- (uint16_t)port;
- (void)setPort:(uint16_t)value;

- (BOOL)start:(NSError **)error;
- (BOOL)stop;

- (void)handleNewConnectionFromAddress:(NSData *)addr inputStream:(NSInputStream *)istr outputStream:(NSOutputStream *)ostr;
// called when a new connection comes in; by default, informs the delegate

@end

@interface TCPServer (TCPServerDelegateMethods)
- (void)TCPServer:(TCPServer *)server didReceiveConnectionFromAddress:(NSData *)addr inputStream:(NSInputStream *)istr outputStream:(NSOutputStream *)ostr;
// if the delegate implements this method, it is called when a new  
// connection comes in; a subclass may, of course, change that behavior
@end

