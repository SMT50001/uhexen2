/*
 * $Id$
 *
 * :ts=8
 *
 * 'Roadshow' -- Amiga TCP/IP stack; "usergroup.library" API
 * Copyright � 2001-2016 by Olaf Barthel.
 * All Rights Reserved.
 *
 * Amiga specific TCP/IP 'C' header files;
 * Freely Distributable
 */

#ifndef BSDSOCKET_INTERFACE_DEF_H
#define BSDSOCKET_INTERFACE_DEF_H

/*
** This file was machine generated by idltool 53.6.
** Do not edit
*/ 

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
#include <exec/interfaces.h>
#endif

#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef NETINET_IN_H
#include <netinet/in.h>
#endif
#ifndef SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifndef SYS_MBUF_H
#include <sys/mbuf.h>
#endif
#ifndef NET_ROUTE_H
#include <net/route.h>
#endif
#ifndef NETDB_H
#include <netdb.h>
#endif
#ifndef LIBRARIES_BSDSOCKET_H
#include <libraries/bsdsocket.h>
#endif
#ifndef DOS_DOSEXTENS_H
#include <dos/dosextens.h>
#endif

#ifdef __cplusplus
#ifdef __USE_AMIGAOS_NAMESPACE__
namespace AmigaOS {
#endif
extern "C" {
#endif

struct SocketIFace
{
	struct InterfaceData Data;

	uint32 APICALL (*Obtain)(struct SocketIFace *Self);
	uint32 APICALL (*Release)(struct SocketIFace *Self);
	void APICALL (*Expunge)(struct SocketIFace *Self);
	struct Interface * APICALL (*Clone)(struct SocketIFace *Self);
	LONG APICALL (*socket)(struct SocketIFace *Self, LONG domain, LONG type, LONG protocol);
	LONG APICALL (*bind)(struct SocketIFace *Self, LONG sock, struct sockaddr * name, socklen_t namelen);
	LONG APICALL (*listen)(struct SocketIFace *Self, LONG sock, LONG backlog);
	LONG APICALL (*accept)(struct SocketIFace *Self, LONG sock, struct sockaddr * addr, socklen_t * addrlen);
	LONG APICALL (*connect)(struct SocketIFace *Self, LONG sock, struct sockaddr * name, socklen_t namelen);
	LONG APICALL (*sendto)(struct SocketIFace *Self, LONG sock, APTR buf, LONG len, LONG flags, struct sockaddr * to, socklen_t tolen);
	LONG APICALL (*send)(struct SocketIFace *Self, LONG sock, APTR buf, LONG len, LONG flags);
	LONG APICALL (*recvfrom)(struct SocketIFace *Self, LONG sock, APTR buf, LONG len, LONG flags, struct sockaddr * addr, socklen_t * addrlen);
	LONG APICALL (*recv)(struct SocketIFace *Self, LONG sock, APTR buf, LONG len, LONG flags);
	LONG APICALL (*shutdown)(struct SocketIFace *Self, LONG sock, LONG how);
	LONG APICALL (*setsockopt)(struct SocketIFace *Self, LONG sock, LONG level, LONG optname, APTR optval, socklen_t optlen);
	LONG APICALL (*getsockopt)(struct SocketIFace *Self, LONG sock, LONG level, LONG optname, APTR optval, socklen_t * optlen);
	LONG APICALL (*getsockname)(struct SocketIFace *Self, LONG sock, struct sockaddr * name, socklen_t * namelen);
	LONG APICALL (*getpeername)(struct SocketIFace *Self, LONG sock, struct sockaddr * name, socklen_t * namelen);
	LONG APICALL (*IoctlSocket)(struct SocketIFace *Self, LONG sock, ULONG req, APTR argp);
	LONG APICALL (*CloseSocket)(struct SocketIFace *Self, LONG sock);
	LONG APICALL (*WaitSelect)(struct SocketIFace *Self, LONG nfds, APTR read_fds, APTR write_fds, APTR except_fds, struct timeval * _timeout, ULONG * signals);
	VOID APICALL (*SetSocketSignals)(struct SocketIFace *Self, ULONG int_mask, ULONG io_mask, ULONG urgent_mask);
	LONG APICALL (*getdtablesize)(struct SocketIFace *Self);
	LONG APICALL (*ObtainSocket)(struct SocketIFace *Self, LONG id, LONG domain, LONG type, LONG protocol);
	LONG APICALL (*ReleaseSocket)(struct SocketIFace *Self, LONG sock, LONG id);
	LONG APICALL (*ReleaseCopyOfSocket)(struct SocketIFace *Self, LONG sock, LONG id);
	LONG APICALL (*Errno)(struct SocketIFace *Self);
	VOID APICALL (*SetErrnoPtr)(struct SocketIFace *Self, APTR errno_ptr, LONG size);
	STRPTR APICALL (*Inet_NtoA)(struct SocketIFace *Self, in_addr_t ip);
	in_addr_t APICALL (*inet_addr)(struct SocketIFace *Self, STRPTR cp);
	in_addr_t APICALL (*Inet_LnaOf)(struct SocketIFace *Self, in_addr_t in);
	in_addr_t APICALL (*Inet_NetOf)(struct SocketIFace *Self, in_addr_t in);
	in_addr_t APICALL (*Inet_MakeAddr)(struct SocketIFace *Self, in_addr_t net, in_addr_t host);
	in_addr_t APICALL (*inet_network)(struct SocketIFace *Self, STRPTR cp);
	struct hostent * APICALL (*gethostbyname)(struct SocketIFace *Self, STRPTR name);
	struct hostent * APICALL (*gethostbyaddr)(struct SocketIFace *Self, STRPTR addr, LONG len, LONG type);
	struct netent * APICALL (*getnetbyname)(struct SocketIFace *Self, STRPTR name);
	struct netent * APICALL (*getnetbyaddr)(struct SocketIFace *Self, in_addr_t net, LONG type);
	struct servent * APICALL (*getservbyname)(struct SocketIFace *Self, STRPTR name, STRPTR proto);
	struct servent * APICALL (*getservbyport)(struct SocketIFace *Self, LONG port, STRPTR proto);
	struct protoent * APICALL (*getprotobyname)(struct SocketIFace *Self, STRPTR name);
	struct protoent * APICALL (*getprotobynumber)(struct SocketIFace *Self, LONG proto);
	VOID APICALL (*vsyslog)(struct SocketIFace *Self, LONG pri, STRPTR msg, APTR args);
	VOID APICALL (*syslog)(struct SocketIFace *Self, LONG pri, STRPTR msg, ...);
	LONG APICALL (*Dup2Socket)(struct SocketIFace *Self, LONG old_socket, LONG new_socket);
	LONG APICALL (*sendmsg)(struct SocketIFace *Self, LONG sock, struct msghdr * msg, LONG flags);
	LONG APICALL (*recvmsg)(struct SocketIFace *Self, LONG sock, struct msghdr * msg, LONG flags);
	LONG APICALL (*gethostname)(struct SocketIFace *Self, STRPTR name, LONG namelen);
	in_addr_t APICALL (*gethostid)(struct SocketIFace *Self);
	LONG APICALL (*SocketBaseTagList)(struct SocketIFace *Self, struct TagItem * tags);
	LONG APICALL (*SocketBaseTags)(struct SocketIFace *Self, ...);
	LONG APICALL (*GetSocketEvents)(struct SocketIFace *Self, ULONG * event_ptr);
	void APICALL (*Reserved1)(struct SocketIFace *Self);
	void APICALL (*Reserved2)(struct SocketIFace *Self);
	void APICALL (*Reserved3)(struct SocketIFace *Self);
	void APICALL (*Reserved4)(struct SocketIFace *Self);
	void APICALL (*Reserved5)(struct SocketIFace *Self);
	void APICALL (*Reserved6)(struct SocketIFace *Self);
	void APICALL (*Reserved7)(struct SocketIFace *Self);
	void APICALL (*Reserved8)(struct SocketIFace *Self);
	void APICALL (*Reserved9)(struct SocketIFace *Self);
	void APICALL (*Reserved10)(struct SocketIFace *Self);
	LONG APICALL (*bpf_open)(struct SocketIFace *Self, LONG channel);
	LONG APICALL (*bpf_close)(struct SocketIFace *Self, LONG channel);
	LONG APICALL (*bpf_read)(struct SocketIFace *Self, LONG channel, APTR buffer, LONG len);
	LONG APICALL (*bpf_write)(struct SocketIFace *Self, LONG channel, APTR buffer, LONG len);
	LONG APICALL (*bpf_set_notify_mask)(struct SocketIFace *Self, LONG channel, ULONG signal_mask);
	LONG APICALL (*bpf_set_interrupt_mask)(struct SocketIFace *Self, LONG channel, ULONG signal_mask);
	LONG APICALL (*bpf_ioctl)(struct SocketIFace *Self, LONG channel, ULONG command, APTR buffer);
	LONG APICALL (*bpf_data_waiting)(struct SocketIFace *Self, LONG channel);
	LONG APICALL (*AddRouteTagList)(struct SocketIFace *Self, struct TagItem * tags);
	LONG APICALL (*AddRouteTags)(struct SocketIFace *Self, ...);
	LONG APICALL (*DeleteRouteTagList)(struct SocketIFace *Self, struct TagItem * tags);
	LONG APICALL (*DeleteRouteTags)(struct SocketIFace *Self, ...);
	LONG APICALL (*ChangeRouteTagList)(struct SocketIFace *Self, struct TagItem * tags);
	LONG APICALL (*ChangeRouteTags)(struct SocketIFace *Self, ...);
	VOID APICALL (*FreeRouteInfo)(struct SocketIFace *Self, struct rt_msghdr * buf);
	struct rt_msghdr * APICALL (*GetRouteInfo)(struct SocketIFace *Self, LONG address_family, LONG flags);
	LONG APICALL (*AddInterfaceTagList)(struct SocketIFace *Self, STRPTR interface_name, STRPTR device_name, LONG unit, struct TagItem * tags);
	LONG APICALL (*AddInterfaceTags)(struct SocketIFace *Self, STRPTR interface_name, STRPTR device_name, LONG unit, ...);
	LONG APICALL (*ConfigureInterfaceTagList)(struct SocketIFace *Self, STRPTR interface_name, struct TagItem * tags);
	LONG APICALL (*ConfigureInterfaceTags)(struct SocketIFace *Self, STRPTR interface_name, ...);
	VOID APICALL (*ReleaseInterfaceList)(struct SocketIFace *Self, struct List * list);
	struct List * APICALL (*ObtainInterfaceList)(struct SocketIFace *Self);
	LONG APICALL (*QueryInterfaceTagList)(struct SocketIFace *Self, STRPTR interface_name, struct TagItem * tags);
	LONG APICALL (*QueryInterfaceTags)(struct SocketIFace *Self, STRPTR interface_name, ...);
	LONG APICALL (*CreateAddrAllocMessageA)(struct SocketIFace *Self, LONG version, LONG protocol, STRPTR interface_name, struct AddressAllocationMessage ** result_ptr, struct TagItem * tags);
	LONG APICALL (*CreateAddrAllocMessage)(struct SocketIFace *Self, LONG version, LONG protocol, STRPTR interface_name, struct AddressAllocationMessage ** result_ptr, ...);
	VOID APICALL (*DeleteAddrAllocMessage)(struct SocketIFace *Self, struct AddressAllocationMessage * aam);
	VOID APICALL (*BeginInterfaceConfig)(struct SocketIFace *Self, struct AddressAllocationMessage * message);
	VOID APICALL (*AbortInterfaceConfig)(struct SocketIFace *Self, struct AddressAllocationMessage * message);
	LONG APICALL (*AddNetMonitorHookTagList)(struct SocketIFace *Self, LONG type, struct Hook * hook, struct TagItem * tags);
	LONG APICALL (*AddNetMonitorHookTags)(struct SocketIFace *Self, LONG type, struct Hook * hook, ...);
	VOID APICALL (*RemoveNetMonitorHook)(struct SocketIFace *Self, struct Hook * hook);
	LONG APICALL (*GetNetworkStatistics)(struct SocketIFace *Self, LONG type, LONG version, APTR destination, LONG size);
	LONG APICALL (*AddDomainNameServer)(struct SocketIFace *Self, STRPTR address);
	LONG APICALL (*RemoveDomainNameServer)(struct SocketIFace *Self, STRPTR address);
	VOID APICALL (*ReleaseDomainNameServerList)(struct SocketIFace *Self, struct List * list);
	struct List * APICALL (*ObtainDomainNameServerList)(struct SocketIFace *Self);
	VOID APICALL (*setnetent)(struct SocketIFace *Self, LONG stay_open);
	VOID APICALL (*endnetent)(struct SocketIFace *Self);
	struct netent * APICALL (*getnetent)(struct SocketIFace *Self);
	VOID APICALL (*setprotoent)(struct SocketIFace *Self, LONG stay_open);
	VOID APICALL (*endprotoent)(struct SocketIFace *Self);
	struct protoent * APICALL (*getprotoent)(struct SocketIFace *Self);
	VOID APICALL (*setservent)(struct SocketIFace *Self, LONG stay_open);
	VOID APICALL (*endservent)(struct SocketIFace *Self);
	struct servent * APICALL (*getservent)(struct SocketIFace *Self);
	LONG APICALL (*inet_aton)(struct SocketIFace *Self, STRPTR cp, struct in_addr * addr);
	STRPTR APICALL (*inet_ntop)(struct SocketIFace *Self, LONG af, APTR src, STRPTR dst, LONG size);
	LONG APICALL (*inet_pton)(struct SocketIFace *Self, LONG af, STRPTR src, APTR dst);
	LONG APICALL (*In_LocalAddr)(struct SocketIFace *Self, in_addr_t address);
	LONG APICALL (*In_CanForward)(struct SocketIFace *Self, in_addr_t address);
	struct mbuf * APICALL (*mbuf_copym)(struct SocketIFace *Self, struct mbuf * m, LONG off, LONG len);
	LONG APICALL (*mbuf_copyback)(struct SocketIFace *Self, struct mbuf * m, LONG off, LONG len, APTR cp);
	LONG APICALL (*mbuf_copydata)(struct SocketIFace *Self, struct mbuf * m, LONG off, LONG len, APTR cp);
	struct mbuf * APICALL (*mbuf_free)(struct SocketIFace *Self, struct mbuf * m);
	VOID APICALL (*mbuf_freem)(struct SocketIFace *Self, struct mbuf * m);
	struct mbuf * APICALL (*mbuf_get)(struct SocketIFace *Self);
	struct mbuf * APICALL (*mbuf_gethdr)(struct SocketIFace *Self);
	struct mbuf * APICALL (*mbuf_prepend)(struct SocketIFace *Self, struct mbuf * m, LONG len);
	LONG APICALL (*mbuf_cat)(struct SocketIFace *Self, struct mbuf * m, struct mbuf * n);
	LONG APICALL (*mbuf_adj)(struct SocketIFace *Self, struct mbuf * mp, LONG req_len);
	struct mbuf * APICALL (*mbuf_pullup)(struct SocketIFace *Self, struct mbuf * m, LONG len);
	BOOL APICALL (*ProcessIsServer)(struct SocketIFace *Self, struct Process * pr);
	LONG APICALL (*ObtainServerSocket)(struct SocketIFace *Self);
	BOOL APICALL (*GetDefaultDomainName)(struct SocketIFace *Self, STRPTR buffer, LONG buffer_size);
	VOID APICALL (*SetDefaultDomainName)(struct SocketIFace *Self, STRPTR buffer);
	struct List * APICALL (*ObtainRoadshowData)(struct SocketIFace *Self, LONG access);
	VOID APICALL (*ReleaseRoadshowData)(struct SocketIFace *Self, struct List * list);
	BOOL APICALL (*ChangeRoadshowData)(struct SocketIFace *Self, struct List * list, STRPTR name, ULONG length, APTR data);
	LONG APICALL (*RemoveInterface)(struct SocketIFace *Self, STRPTR interface_name, LONG force);
	struct hostent * APICALL (*gethostbyname_r)(struct SocketIFace *Self, STRPTR name, struct hostent * hp, APTR buf, ULONG buflen, LONG * he);
	struct hostent * APICALL (*gethostbyaddr_r)(struct SocketIFace *Self, STRPTR addr, LONG len, LONG type, struct hostent * hp, APTR buf, ULONG buflen, LONG * he);
	void APICALL (*Reserved11)(struct SocketIFace *Self);
	void APICALL (*Reserved12)(struct SocketIFace *Self);
	LONG APICALL (*ipf_open)(struct SocketIFace *Self, LONG channel);
	LONG APICALL (*ipf_close)(struct SocketIFace *Self, LONG channel);
	LONG APICALL (*ipf_ioctl)(struct SocketIFace *Self, LONG channel, ULONG command, APTR buffer);
	LONG APICALL (*ipf_log_read)(struct SocketIFace *Self, LONG channel, APTR buffer, LONG len);
	LONG APICALL (*ipf_log_data_waiting)(struct SocketIFace *Self, LONG channel);
	LONG APICALL (*ipf_set_notify_mask)(struct SocketIFace *Self, LONG channel, ULONG mask);
	LONG APICALL (*ipf_set_interrupt_mask)(struct SocketIFace *Self, LONG channel, ULONG mask);
	VOID APICALL (*freeaddrinfo)(struct SocketIFace *Self, struct addrinfo * ai);
	LONG APICALL (*getaddrinfo)(struct SocketIFace *Self, STRPTR hostname, STRPTR servname, struct addrinfo * hints, struct addrinfo ** res);
	STRPTR APICALL (*gai_strerror)(struct SocketIFace *Self, LONG errnum);
	LONG APICALL (*getnameinfo)(struct SocketIFace *Self, struct sockaddr * sa, ULONG salen, STRPTR host, ULONG hostlen, STRPTR serv, ULONG servlen, ULONG flags);
};

#ifdef __cplusplus
}
#ifdef __USE_AMIGAOS_NAMESPACE__
}
#endif
#endif

#endif /* BSDSOCKET_INTERFACE_DEF_H */
