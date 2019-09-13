    #include <stdint.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/mman.h>
     
    #define INTC_SUCCESS 0 

    static int file;
     
    // Initializes the driver (opens UIO file and calls mmap)
    // devDevice: The file path to the uio dev file
    // Returns: A negative error code on error, INTC_SUCCESS otherwise
    // This must be called before calling any other intc_* functions
    int32_t intc_init(char devDevice[])
    {
        file = open(devDevice, O_RDWR);

        if (file == UIO_EXAMPLE_ERROR)
        {
            //file descriptors have to be > 0 to be valid
            return UIO_EXAMPLE_ERROR;
        }

        //memory map the physical address of the hardware into virtual address space
        ptr = mmap(NULL, UIO_EXAMPLE_MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file, MMAP_OFFSET);
        if (ptr == MAP_FAILED)
        {
            return UIO_EXAMPLE_ERROR;
        }

        /* put hardware setup here */

        return UIO_EXAMPLE_SUCCESS;
    }

    // write to a register of the UIO device
    void generic_write(uint32_t offset, uint32_t value)
    {
        //the address is cast as a pointer so it can be dereferenced
        *((volatile uint32_t *)(ptr + offset)) = value;
    }

    // read from a register of the UIO device
    uint32_t generic_read(uint32_t offset)
    {
        return *((volatile uint32_t *)(ptr + offset));
    }

    // close the UIO device
    //	this function must be called after all read/write operations are done
    //	to properly unmap the memory and close the file descriptor
    void generic_exit()
    {
        munmap(ptr, UIO_EXAMPLE_MMAP_SIZE);
        close(file);
    }

    // Called to exit the driver (unmap and close UIO file)
    void intc_exit()
    {

    }
     
    // This function will block until an interrupt occurs
    // Returns: Bitmask of activated interrupts
    uint32_t intc_wait_for_interrupt()
    {

    }
     
    // Acknowledge interrupt(s) in the interrupt controller
    // irq_mask: Bitmask of interrupt lines to acknowledge.
    void intc_ack_interrupt(uint32_t irq_mask)
    {

    }
     
    // Instruct the UIO to enable interrupts for this device in Linux
    // (see the UIO documentation for how to do this)
    void intc_enable_uio_interrupts()
    {

    }
     
    // Enable interrupt line(s)
    // irq_mask: Bitmask of lines to enable
    // This function only enables interrupt lines, ie, a 0 bit in irq_mask
    //	will not disable the interrupt line
    void intc_irq_enable(uint32_t irq_mask)
    {

    }
     
    // Same as intc_irq_enable, except this disables interrupt lines
    void intc_irq_disable(uint32_t irq_mask)
    {
        
    }

