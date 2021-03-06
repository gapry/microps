#ifndef _ETHERNET_H_
#define _ETHERNET_H_

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>

#define ETHERNET_ADDR_LEN 6
#define ETHERNET_ADDR_STR_LEN 17

#define ETHERNET_HDR_SIZE 14
#define ETHERNET_TRL_SIZE 4
#define ETHERNET_FRAME_SIZE_MIN 64
#define ETHERNET_FRAME_SIZE_MAX 1518
#define ETHERNET_PAYLOAD_SIZE_MIN (ETHERNET_FRAME_SIZE_MIN - (ETHERNET_HDR_SIZE + ETHERNET_TRL_SIZE))
#define ETHERNET_PAYLOAD_SIZE_MAX (ETHERNET_FRAME_SIZE_MAX - (ETHERNET_HDR_SIZE + ETHERNET_TRL_SIZE))

#define ETHERNET_TYPE_IP 0x0800
#define ETHERNET_TYPE_ARP 0x0806
#define ETHERNET_TYPE_LOOPBACK 0x9000

struct ethernet_device;

typedef struct {
    uint8_t addr[ETHERNET_ADDR_LEN];
} __attribute__ ((packed)) ethernet_addr_t;

extern const ethernet_addr_t ETHERNET_ADDR_BCAST;

extern int
ethernet_addr_pton (const char *p, ethernet_addr_t *n);
extern char *
ethernet_addr_ntop (const ethernet_addr_t *n, char *p, size_t size);
extern int
ethernet_init (void);
extern int
ethernet_add_protocol (uint16_t type, void (*callback)(uint8_t *, size_t, void *));
extern ssize_t
ethernet_output (struct ethernet_device *, uint16_t type, const uint8_t *payload, size_t plen, const ethernet_addr_t *dst);
extern struct ethernet_device *
ethernet_device_open (const char *name, const char *addr);
extern void
ethernet_device_close (struct ethernet_device *);
extern ethernet_addr_t *
ethernet_device_addr (struct ethernet_device *, ethernet_addr_t *dst);
extern int
ethernet_device_run (struct ethernet_device *);

#endif
