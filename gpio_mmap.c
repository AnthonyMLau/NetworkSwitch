#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> 


#define DB410C_MMAP_REG 0x01000000
#define MRAA_96BOARDS_LS_GPIO_COUNT 12
#define SUCCESS 0
#define FAILURE 1
#define MMAP_PATH "/dev/mem"


#define MRAA_96BOARDS_LS_GPIO_COUNT 12
#define MRAA_96BOARDS_LS_I2C_COUNT  2
#define MRAA_96BOARDS_LS_SPI_COUNT  1
#define MRAA_96BOARDS_LS_UART_COUNT 2
#define MRAA_96BOARDS_LS_PIN_COUNT  40
#define MRAA_96BOARDS_LED_COUNT 6
#define MAP_FAILED	((void *) -1)


// MMAP
static uint8_t* mmap_reg = NULL;
static int mmap_fd = 0;
static int mmap_size = 0x00120004;
static unsigned int mmap_count = 0;

int db410c_ls_gpio_pins[MRAA_96BOARDS_LS_GPIO_COUNT] = {
    36, 12, 13, 69, 115, 4, 24, 25, 35, 34, 28, 33,
};

int db410c_chardev_map[MRAA_96BOARDS_LS_GPIO_COUNT][2] = {
    { 0, 36 }, { 0, 12 }, { 0, 13 }, { 0, 69 }, { 0, 115 }, { 2, 3 },
    { 0, 24 }, { 0, 25 }, { 0, 35 }, { 0, 34 }, { 0, 28 },  { 0, 33 },
};

const char* db410c_serialdev[MRAA_96BOARDS_LS_UART_COUNT] = { "/dev/ttyMSM0", "/dev/ttyMSM1" };
const char* db410c_led[MRAA_96BOARDS_LED_COUNT] = { "user1", "user2", "user3",
                                                    "user4", "bt", "wlan" };



int mraa_db410c_mmap_unsetup()
{
    if (mmap_reg == NULL) {
        // syslog(LOG_WARNING, "db410c mmap: null register nothing to unsetup");
        return FAILURE;
    }
    munmap(mmap_reg, mmap_size);
    mmap_reg = NULL;
    close(mmap_fd);

    return SUCCESS;
}

int mraa_db410c_mmap_write(int pin, int value)
{
    uint32_t offset = (0x1000 * pin);

    if (value) {
        *(volatile uint32_t*) (mmap_reg + offset + 0x04) |= (uint32_t)(1 << 1);
    } else {
        *(volatile uint32_t*) (mmap_reg + offset + 0x04) &= ~(uint32_t)(1 << 1);
    }

    return SUCCESS;
}

int mraa_db410c_mmap_read(int pin)
{
    uint32_t value;
    uint32_t offset = (0x1000 * pin);

    value = *(volatile uint32_t*) (mmap_reg + offset + 0x04);
    if (value & (uint32_t)(1 << 0)) {
        return 1;
    }

    return 0;
}

int mraa_db410c_mmap_setup(int pin)
{
    if (pin == 0) {
        // syslog(LOG_ERR, "db410c mmap: context not valid");
        return FAILURE;
    }

    if (mmap_reg == NULL) {
        if ((mmap_fd = open(MMAP_PATH, O_RDWR)) < 0) {
            printf("db410c mmap: unable to open /dev/mem\n");
            return FAILURE;
        }
        mmap_reg = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, mmap_fd, DB410C_MMAP_REG);

        if (mmap_reg == MAP_FAILED) {
            printf("db410c mmap: failed to mmap\n");
            mmap_reg = NULL;
            close(mmap_fd);
            return FAILURE;
        }
    }
    mmap_count++;

    return SUCCESS;
}

int main()
{
    int pin = 1;
    // printf("Which pin?: ");
    // int pin = 0;
    // scanf("%i", &pin);

    // printf("What value?: ");
    // int value = 0;
    // scanf("%i", &value);
    
    if( !mraa_db410c_mmap_setup(pin) == SUCCESS ){
        printf("setup failed\n");
        return 0;
    }

    // mraa_db410c_mmap_write(pin, value);
    for (pin = 1; pin < 500; pin++)
    {
        // sleep(1);
        printf("start pin %i\n", pin);
        mraa_db410c_mmap_write(pin, 1);
        printf("finished pin %i\n", pin);
    }
    

}