typedef struct
{
    volatile uint32_t               tx_buffer_size;  //!< SPI slave TX buffer size in bytes.
    volatile uint32_t               rx_buffer_size;  //!< SPI slave RX buffer size in bytes.
    nrfx_spis_event_handler_t       handler;         //!< SPI event handler.
    volatile const uint8_t *        tx_buffer;       //!< SPI slave TX buffer.
    volatile uint8_t *              rx_buffer;       //!< SPI slave RX buffer.
    nrfx_drv_state_t                state;           //!< driver initialization state.
    volatile nrfx_spis_state_t      spi_state;       //!< SPI slave state.
    void *                          p_context;       //!< Context set on initialization.
} spis_cb_t;

typedef struct
{
    volatile uint32_t tx_buffer_size; //!< SPI slave TX buffer size in bytes.
    volatile uint32_t rx_buffer_size; //!< SPI slave RX buffer size in bytes.
    nrfx_spis_event_handler_t handler; //!< SPI event handler.
    volatile const uint8_t * tx_buffer; //!< SPI slave TX buffer.
    volatile uint8_t * rx_buffer; //!< SPI slave RX buffer.
    nrfx_drv_state_t state; //!< driver initialization state.
    volatile nrfx_spis_state_t spi_state; //!< SPI slave state.
    void * p_context; //!< Context set on initialization.
} spis_cb_t;