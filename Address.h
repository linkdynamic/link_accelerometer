//Define All EPPROM the Address 

#define BUILD_COUNT_ADDR   2           //2
#define UUID_ADDR  66                  //64
#define SSID_ADDR  98                  //32
#define PWD_ADDR   130                 //32
#define API_KEY_ADDR  194              //64
#define WEB_UID_ADDR  226              //32
#define WEB_PWD_ADDR  250              //24
#define PIN_NUMBER_ADDR  266           //16
#define DEVICE_UID_ADDR  274           //8
#define DEVICE_PWD_ADDR  290           //16
#define DEVICE_MEASURE_KV_ADDR  322    //32
#define LOGIN_ADDR       326           //4
#define LOGIN_TIMESTAMP_ADDR  342      //16
#define SD_ONLY_ADDR          344      //2
#define BUFFER_SIZE_ADDR      346      //2
#define SAMPLE_RATE_ADDR      350      //4
#define ENCRYPT_SECRET_ADDR   366      //16
#define WEB_HOST_ADDR         430      //64



//ADXL345 Register Addresses
#define DEVID           0x00  //Device ID Register
#define THRESH_TAP      0x1D  //Tap Threshold
#define OFSX            0x1E  //X-axis offset
#define OFSY            0x1F  //Y-axis offset
#define OFSZ            0x20  //Z-axis offset
#define DURATION        0x21  //Tap Duration
#define LATENT          0x22  //Tap latency
#define WINDOW          0x23  //Tap window
#define THRESH_ACT      0x24  //Activity Threshold
#define THRESH_INACT    0x25  //Inactivity Threshold
#define TIME_INACT      0x26  //Inactivity Time
#define ACT_INACT_CTL   0x27  //Axis enable control for activity and inactivity detection
#define THRESH_FF       0x28  //free-fall threshold
#define TIME_FF         0x29  //Free-Fall Time
#define TAP_AXES        0x2A  //Axis control for tap/double tap
#define ACT_TAP_STATUS  0x2B  //Source of tap/double tap
#define BW_RATE         0x2C  //Data rate and power mode control
#define POWER_CTL       0x2D  //Power Control Register
#define INT_ENABLE      0x2E  //Interrupt Enable Control
#define INT_MAP         0x2F  //Interrupt Mapping Control
#define INT_SOURCE      0x30  //Source of interrupts
#define DATA_FORMAT     0x31  //Data format control
#define DATAX0          0x32  //X-Axis Data 0
#define DATAX1          0x33  //X-Axis Data 1
#define DATAY0          0x34  //Y-Axis Data 0
#define DATAY1          0x35  //Y-Axis Data 1
#define DATAZ0          0x36  //Z-Axis Data 0
#define DATAZ1          0x37  //Z-Axis Data 1
#define FIFO_CTL        0x38  //FIFO control
#define FIFO_STATUS     0x39  //FIFO status
