#include<sys/socket.h>
#include<sys/types.h>
#include<bluetooth/bluetooth.h>
#include<bluetooth/hci.h>
#include<stdlib.h>
#include<unistd.h>
void print_hex(const unsigned char *buff, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", buff[i]);  // Print each byte as a two-digit hex number

        if ((i + 1) % 16 == 0) {   // Add a newline after every 16 bytes for readability
            printf("\t");
            for(size_t j=i-15;j<=i;j++){
                if (buff[j] >= 32 && buff[j] <= 126) {
                    printf("%c", buff[j]);
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }
    size_t remainder = len%16;
    if (remainder!=0) {
        for(size_t i=16-remainder;i>0;i--) printf("   ");
        printf("\t");
        for(size_t j=len-remainder;j<len;j++){
            if (buff[j] >= 32 && buff[j] <= 126) {
                printf("%c", buff[j]);
            } else {
                printf(".");
            }
        }   
        printf("\n");
    }
}
void main(){
    int fd = socket(AF_BLUETOOTH, SOCK_RAW|SOCK_CLOEXEC, BTPROTO_HCI);
    if(fd<0){
        perror("[-] Error creating socket!\n");
        exit(0);
    }
    struct sockaddr_hci addr;
    addr.hci_family = AF_BLUETOOTH;
    addr.hci_dev = htobs(65535);
    addr.hci_channel = HCI_CHANNEL_MONITOR;

    int result = bind(fd, (struct sockaddr *)&addr, 6);
    if(result<0){
        perror("[-] Error binding\n");
        close(fd);
        exit(0);
    }
    printf("[+] Monitoring Started\n");
    int len = 0;
    while(1){
        unsigned char buff[1024];
        len = recv(fd, buff, 1024, MSG_DONTWAIT);
        if(len>0){
            printf("L=%d\n", len);
            print_hex(buff, len);
            printf("\n\n");
        }
    }
}
