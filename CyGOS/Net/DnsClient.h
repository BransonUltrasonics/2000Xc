// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/Net/DnsClient.h_v   1.2   05 Mar 2014 13:58:26   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This module defines DNS resolver (client) object.

#ifndef DNS_H_
#define DNS_H_

#define LWIP_DNS 1

#define DNS_MAX_SERVERS                 2

struct ip_addr;

void dns_setserver(int numdns, ip_addr * dnsserver);

#endif
