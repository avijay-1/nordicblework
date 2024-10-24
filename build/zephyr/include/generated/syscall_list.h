/* auto-generated by gen_syscalls.py, don't edit */

#ifndef ZEPHYR_SYSCALL_LIST_H
#define ZEPHYR_SYSCALL_LIST_H

#define K_SYSCALL_ADC_CHANNEL_SETUP 0
#define K_SYSCALL_ADC_READ 1
#define K_SYSCALL_ADC_READ_ASYNC 2
#define K_SYSCALL_CLOCK_GETTIME 3
#define K_SYSCALL_DEVICE_GET_BINDING 4
#define K_SYSCALL_DEVICE_IS_READY 5
#define K_SYSCALL_GPIO_GET_PENDING_INT 6
#define K_SYSCALL_GPIO_PIN_CONFIGURE 7
#define K_SYSCALL_GPIO_PIN_GET_CONFIG 8
#define K_SYSCALL_GPIO_PIN_INTERRUPT_CONFIGURE 9
#define K_SYSCALL_GPIO_PORT_CLEAR_BITS_RAW 10
#define K_SYSCALL_GPIO_PORT_GET_DIRECTION 11
#define K_SYSCALL_GPIO_PORT_GET_RAW 12
#define K_SYSCALL_GPIO_PORT_SET_BITS_RAW 13
#define K_SYSCALL_GPIO_PORT_SET_MASKED_RAW 14
#define K_SYSCALL_GPIO_PORT_TOGGLE_BITS 15
#define K_SYSCALL_K_BUSY_WAIT 16
#define K_SYSCALL_K_CONDVAR_BROADCAST 17
#define K_SYSCALL_K_CONDVAR_INIT 18
#define K_SYSCALL_K_CONDVAR_SIGNAL 19
#define K_SYSCALL_K_CONDVAR_WAIT 20
#define K_SYSCALL_K_EVENT_CLEAR 21
#define K_SYSCALL_K_EVENT_INIT 22
#define K_SYSCALL_K_EVENT_POST 23
#define K_SYSCALL_K_EVENT_SET 24
#define K_SYSCALL_K_EVENT_SET_MASKED 25
#define K_SYSCALL_K_EVENT_WAIT 26
#define K_SYSCALL_K_EVENT_WAIT_ALL 27
#define K_SYSCALL_K_FLOAT_DISABLE 28
#define K_SYSCALL_K_FLOAT_ENABLE 29
#define K_SYSCALL_K_FUTEX_WAIT 30
#define K_SYSCALL_K_FUTEX_WAKE 31
#define K_SYSCALL_K_IS_PREEMPT_THREAD 32
#define K_SYSCALL_K_MSGQ_ALLOC_INIT 33
#define K_SYSCALL_K_MSGQ_GET 34
#define K_SYSCALL_K_MSGQ_GET_ATTRS 35
#define K_SYSCALL_K_MSGQ_NUM_FREE_GET 36
#define K_SYSCALL_K_MSGQ_NUM_USED_GET 37
#define K_SYSCALL_K_MSGQ_PEEK 38
#define K_SYSCALL_K_MSGQ_PEEK_AT 39
#define K_SYSCALL_K_MSGQ_PURGE 40
#define K_SYSCALL_K_MSGQ_PUT 41
#define K_SYSCALL_K_MUTEX_INIT 42
#define K_SYSCALL_K_MUTEX_LOCK 43
#define K_SYSCALL_K_MUTEX_UNLOCK 44
#define K_SYSCALL_K_OBJECT_ACCESS_GRANT 45
#define K_SYSCALL_K_OBJECT_ALLOC 46
#define K_SYSCALL_K_OBJECT_ALLOC_SIZE 47
#define K_SYSCALL_K_OBJECT_RELEASE 48
#define K_SYSCALL_K_PIPE_ALLOC_INIT 49
#define K_SYSCALL_K_PIPE_BUFFER_FLUSH 50
#define K_SYSCALL_K_PIPE_FLUSH 51
#define K_SYSCALL_K_PIPE_GET 52
#define K_SYSCALL_K_PIPE_PUT 53
#define K_SYSCALL_K_PIPE_READ_AVAIL 54
#define K_SYSCALL_K_PIPE_WRITE_AVAIL 55
#define K_SYSCALL_K_POLL 56
#define K_SYSCALL_K_POLL_SIGNAL_CHECK 57
#define K_SYSCALL_K_POLL_SIGNAL_INIT 58
#define K_SYSCALL_K_POLL_SIGNAL_RAISE 59
#define K_SYSCALL_K_POLL_SIGNAL_RESET 60
#define K_SYSCALL_K_QUEUE_ALLOC_APPEND 61
#define K_SYSCALL_K_QUEUE_ALLOC_PREPEND 62
#define K_SYSCALL_K_QUEUE_CANCEL_WAIT 63
#define K_SYSCALL_K_QUEUE_GET 64
#define K_SYSCALL_K_QUEUE_INIT 65
#define K_SYSCALL_K_QUEUE_IS_EMPTY 66
#define K_SYSCALL_K_QUEUE_PEEK_HEAD 67
#define K_SYSCALL_K_QUEUE_PEEK_TAIL 68
#define K_SYSCALL_K_SCHED_CURRENT_THREAD_QUERY 69
#define K_SYSCALL_K_SEM_COUNT_GET 70
#define K_SYSCALL_K_SEM_GIVE 71
#define K_SYSCALL_K_SEM_INIT 72
#define K_SYSCALL_K_SEM_RESET 73
#define K_SYSCALL_K_SEM_TAKE 74
#define K_SYSCALL_K_SLEEP 75
#define K_SYSCALL_K_STACK_ALLOC_INIT 76
#define K_SYSCALL_K_STACK_POP 77
#define K_SYSCALL_K_STACK_PUSH 78
#define K_SYSCALL_K_STR_OUT 79
#define K_SYSCALL_K_THREAD_ABORT 80
#define K_SYSCALL_K_THREAD_CREATE 81
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_GET 82
#define K_SYSCALL_K_THREAD_CUSTOM_DATA_SET 83
#define K_SYSCALL_K_THREAD_DEADLINE_SET 84
#define K_SYSCALL_K_THREAD_JOIN 85
#define K_SYSCALL_K_THREAD_NAME_COPY 86
#define K_SYSCALL_K_THREAD_NAME_SET 87
#define K_SYSCALL_K_THREAD_PRIORITY_GET 88
#define K_SYSCALL_K_THREAD_PRIORITY_SET 89
#define K_SYSCALL_K_THREAD_RESUME 90
#define K_SYSCALL_K_THREAD_STACK_ALLOC 91
#define K_SYSCALL_K_THREAD_STACK_FREE 92
#define K_SYSCALL_K_THREAD_STACK_SPACE_GET 93
#define K_SYSCALL_K_THREAD_START 94
#define K_SYSCALL_K_THREAD_SUSPEND 95
#define K_SYSCALL_K_THREAD_TIMEOUT_EXPIRES_TICKS 96
#define K_SYSCALL_K_THREAD_TIMEOUT_REMAINING_TICKS 97
#define K_SYSCALL_K_TIMER_EXPIRES_TICKS 98
#define K_SYSCALL_K_TIMER_REMAINING_TICKS 99
#define K_SYSCALL_K_TIMER_START 100
#define K_SYSCALL_K_TIMER_STATUS_GET 101
#define K_SYSCALL_K_TIMER_STATUS_SYNC 102
#define K_SYSCALL_K_TIMER_STOP 103
#define K_SYSCALL_K_TIMER_USER_DATA_GET 104
#define K_SYSCALL_K_TIMER_USER_DATA_SET 105
#define K_SYSCALL_K_UPTIME_TICKS 106
#define K_SYSCALL_K_USLEEP 107
#define K_SYSCALL_K_WAKEUP 108
#define K_SYSCALL_K_YIELD 109
#define K_SYSCALL_LOG_BUFFERED_CNT 110
#define K_SYSCALL_LOG_FILTER_SET 111
#define K_SYSCALL_LOG_PANIC 112
#define K_SYSCALL_LOG_PROCESS 113
#define K_SYSCALL_MBOX_MAX_CHANNELS_GET 114
#define K_SYSCALL_MBOX_MTU_GET 115
#define K_SYSCALL_MBOX_SEND 116
#define K_SYSCALL_MBOX_SET_ENABLED 117
#define K_SYSCALL_SENSOR_ATTR_GET 118
#define K_SYSCALL_SENSOR_ATTR_SET 119
#define K_SYSCALL_SENSOR_CHANNEL_GET 120
#define K_SYSCALL_SENSOR_GET_DECODER 121
#define K_SYSCALL_SENSOR_RECONFIGURE_READ_IODEV 122
#define K_SYSCALL_SENSOR_SAMPLE_FETCH 123
#define K_SYSCALL_SENSOR_SAMPLE_FETCH_CHAN 124
#define K_SYSCALL_SYS_CLOCK_HW_CYCLES_PER_SEC_RUNTIME_GET 125
#define K_SYSCALL_UART_CONFIGURE 126
#define K_SYSCALL_UART_CONFIG_GET 127
#define K_SYSCALL_UART_DRV_CMD 128
#define K_SYSCALL_UART_ERR_CHECK 129
#define K_SYSCALL_UART_IRQ_ERR_DISABLE 130
#define K_SYSCALL_UART_IRQ_ERR_ENABLE 131
#define K_SYSCALL_UART_IRQ_IS_PENDING 132
#define K_SYSCALL_UART_IRQ_RX_DISABLE 133
#define K_SYSCALL_UART_IRQ_RX_ENABLE 134
#define K_SYSCALL_UART_IRQ_TX_DISABLE 135
#define K_SYSCALL_UART_IRQ_TX_ENABLE 136
#define K_SYSCALL_UART_IRQ_UPDATE 137
#define K_SYSCALL_UART_LINE_CTRL_GET 138
#define K_SYSCALL_UART_LINE_CTRL_SET 139
#define K_SYSCALL_UART_POLL_IN 140
#define K_SYSCALL_UART_POLL_IN_U16 141
#define K_SYSCALL_UART_POLL_OUT 142
#define K_SYSCALL_UART_POLL_OUT_U16 143
#define K_SYSCALL_UART_RX_DISABLE 144
#define K_SYSCALL_UART_RX_ENABLE 145
#define K_SYSCALL_UART_RX_ENABLE_U16 146
#define K_SYSCALL_UART_TX 147
#define K_SYSCALL_UART_TX_ABORT 148
#define K_SYSCALL_UART_TX_U16 149
#define K_SYSCALL_ZEPHYR_FPUTC 150
#define K_SYSCALL_ZEPHYR_FWRITE 151
#define K_SYSCALL_ZEPHYR_READ_STDIN 152
#define K_SYSCALL_ZEPHYR_WRITE_STDOUT 153
#define K_SYSCALL_Z_LOG_MSG_SIMPLE_CREATE_0 154
#define K_SYSCALL_Z_LOG_MSG_SIMPLE_CREATE_1 155
#define K_SYSCALL_Z_LOG_MSG_SIMPLE_CREATE_2 156
#define K_SYSCALL_Z_LOG_MSG_STATIC_CREATE 157
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_LOCK 158
#define K_SYSCALL_Z_SYS_MUTEX_KERNEL_UNLOCK 159
#define K_SYSCALL_BAD 160
#define K_SYSCALL_LIMIT 161


/* Following syscalls are not used in image */
#define K_SYSCALL_ATOMIC_ADD 162
#define K_SYSCALL_ATOMIC_AND 163
#define K_SYSCALL_ATOMIC_CAS 164
#define K_SYSCALL_ATOMIC_NAND 165
#define K_SYSCALL_ATOMIC_OR 166
#define K_SYSCALL_ATOMIC_PTR_CAS 167
#define K_SYSCALL_ATOMIC_PTR_SET 168
#define K_SYSCALL_ATOMIC_SET 169
#define K_SYSCALL_ATOMIC_SUB 170
#define K_SYSCALL_ATOMIC_XOR 171
#define K_SYSCALL_AUXDISPLAY_BACKLIGHT_GET 172
#define K_SYSCALL_AUXDISPLAY_BACKLIGHT_SET 173
#define K_SYSCALL_AUXDISPLAY_BRIGHTNESS_GET 174
#define K_SYSCALL_AUXDISPLAY_BRIGHTNESS_SET 175
#define K_SYSCALL_AUXDISPLAY_CAPABILITIES_GET 176
#define K_SYSCALL_AUXDISPLAY_CLEAR 177
#define K_SYSCALL_AUXDISPLAY_CURSOR_POSITION_GET 178
#define K_SYSCALL_AUXDISPLAY_CURSOR_POSITION_SET 179
#define K_SYSCALL_AUXDISPLAY_CURSOR_SET_ENABLED 180
#define K_SYSCALL_AUXDISPLAY_CURSOR_SHIFT_SET 181
#define K_SYSCALL_AUXDISPLAY_CUSTOM_CHARACTER_SET 182
#define K_SYSCALL_AUXDISPLAY_CUSTOM_COMMAND 183
#define K_SYSCALL_AUXDISPLAY_DISPLAY_OFF 184
#define K_SYSCALL_AUXDISPLAY_DISPLAY_ON 185
#define K_SYSCALL_AUXDISPLAY_DISPLAY_POSITION_GET 186
#define K_SYSCALL_AUXDISPLAY_DISPLAY_POSITION_SET 187
#define K_SYSCALL_AUXDISPLAY_IS_BUSY 188
#define K_SYSCALL_AUXDISPLAY_POSITION_BLINKING_SET_ENABLED 189
#define K_SYSCALL_AUXDISPLAY_WRITE 190
#define K_SYSCALL_BBRAM_CHECK_INVALID 191
#define K_SYSCALL_BBRAM_CHECK_POWER 192
#define K_SYSCALL_BBRAM_CHECK_STANDBY_POWER 193
#define K_SYSCALL_BBRAM_GET_SIZE 194
#define K_SYSCALL_BBRAM_READ 195
#define K_SYSCALL_BBRAM_WRITE 196
#define K_SYSCALL_BC12_SET_RESULT_CB 197
#define K_SYSCALL_BC12_SET_ROLE 198
#define K_SYSCALL_CAN_ADD_RX_FILTER_MSGQ 199
#define K_SYSCALL_CAN_CALC_TIMING 200
#define K_SYSCALL_CAN_CALC_TIMING_DATA 201
#define K_SYSCALL_CAN_GET_CAPABILITIES 202
#define K_SYSCALL_CAN_GET_CORE_CLOCK 203
#define K_SYSCALL_CAN_GET_MAX_BITRATE 204
#define K_SYSCALL_CAN_GET_MAX_FILTERS 205
#define K_SYSCALL_CAN_GET_STATE 206
#define K_SYSCALL_CAN_GET_TIMING_DATA_MAX 207
#define K_SYSCALL_CAN_GET_TIMING_DATA_MIN 208
#define K_SYSCALL_CAN_GET_TIMING_MAX 209
#define K_SYSCALL_CAN_GET_TIMING_MIN 210
#define K_SYSCALL_CAN_RECOVER 211
#define K_SYSCALL_CAN_REMOVE_RX_FILTER 212
#define K_SYSCALL_CAN_SEND 213
#define K_SYSCALL_CAN_SET_BITRATE 214
#define K_SYSCALL_CAN_SET_BITRATE_DATA 215
#define K_SYSCALL_CAN_SET_MODE 216
#define K_SYSCALL_CAN_SET_TIMING 217
#define K_SYSCALL_CAN_SET_TIMING_DATA 218
#define K_SYSCALL_CAN_START 219
#define K_SYSCALL_CAN_STATS_GET_ACK_ERRORS 220
#define K_SYSCALL_CAN_STATS_GET_BIT0_ERRORS 221
#define K_SYSCALL_CAN_STATS_GET_BIT1_ERRORS 222
#define K_SYSCALL_CAN_STATS_GET_BIT_ERRORS 223
#define K_SYSCALL_CAN_STATS_GET_CRC_ERRORS 224
#define K_SYSCALL_CAN_STATS_GET_FORM_ERRORS 225
#define K_SYSCALL_CAN_STATS_GET_RX_OVERRUNS 226
#define K_SYSCALL_CAN_STATS_GET_STUFF_ERRORS 227
#define K_SYSCALL_CAN_STOP 228
#define K_SYSCALL_CHARGER_GET_PROP 229
#define K_SYSCALL_CHARGER_SET_PROP 230
#define K_SYSCALL_COUNTER_CANCEL_CHANNEL_ALARM 231
#define K_SYSCALL_COUNTER_GET_FREQUENCY 232
#define K_SYSCALL_COUNTER_GET_GUARD_PERIOD 233
#define K_SYSCALL_COUNTER_GET_MAX_TOP_VALUE 234
#define K_SYSCALL_COUNTER_GET_NUM_OF_CHANNELS 235
#define K_SYSCALL_COUNTER_GET_PENDING_INT 236
#define K_SYSCALL_COUNTER_GET_TOP_VALUE 237
#define K_SYSCALL_COUNTER_GET_VALUE 238
#define K_SYSCALL_COUNTER_GET_VALUE_64 239
#define K_SYSCALL_COUNTER_IS_COUNTING_UP 240
#define K_SYSCALL_COUNTER_SET_CHANNEL_ALARM 241
#define K_SYSCALL_COUNTER_SET_GUARD_PERIOD 242
#define K_SYSCALL_COUNTER_SET_TOP_VALUE 243
#define K_SYSCALL_COUNTER_START 244
#define K_SYSCALL_COUNTER_STOP 245
#define K_SYSCALL_COUNTER_TICKS_TO_US 246
#define K_SYSCALL_COUNTER_US_TO_TICKS 247
#define K_SYSCALL_DAC_CHANNEL_SETUP 248
#define K_SYSCALL_DAC_WRITE_VALUE 249
#define K_SYSCALL_DEVMUX_SELECT_GET 250
#define K_SYSCALL_DEVMUX_SELECT_SET 251
#define K_SYSCALL_DMA_CHAN_FILTER 252
#define K_SYSCALL_DMA_RELEASE_CHANNEL 253
#define K_SYSCALL_DMA_REQUEST_CHANNEL 254
#define K_SYSCALL_DMA_RESUME 255
#define K_SYSCALL_DMA_START 256
#define K_SYSCALL_DMA_STOP 257
#define K_SYSCALL_DMA_SUSPEND 258
#define K_SYSCALL_EEPROM_GET_SIZE 259
#define K_SYSCALL_EEPROM_READ 260
#define K_SYSCALL_EEPROM_WRITE 261
#define K_SYSCALL_EMUL_FUEL_GAUGE_IS_BATTERY_CUTOFF 262
#define K_SYSCALL_EMUL_FUEL_GAUGE_SET_BATTERY_CHARGING 263
#define K_SYSCALL_ENTROPY_GET_ENTROPY 264
#define K_SYSCALL_ESPI_CONFIG 265
#define K_SYSCALL_ESPI_FLASH_ERASE 266
#define K_SYSCALL_ESPI_GET_CHANNEL_STATUS 267
#define K_SYSCALL_ESPI_READ_FLASH 268
#define K_SYSCALL_ESPI_READ_LPC_REQUEST 269
#define K_SYSCALL_ESPI_READ_REQUEST 270
#define K_SYSCALL_ESPI_RECEIVE_OOB 271
#define K_SYSCALL_ESPI_RECEIVE_VWIRE 272
#define K_SYSCALL_ESPI_SAF_ACTIVATE 273
#define K_SYSCALL_ESPI_SAF_CONFIG 274
#define K_SYSCALL_ESPI_SAF_FLASH_ERASE 275
#define K_SYSCALL_ESPI_SAF_FLASH_READ 276
#define K_SYSCALL_ESPI_SAF_FLASH_WRITE 277
#define K_SYSCALL_ESPI_SAF_GET_CHANNEL_STATUS 278
#define K_SYSCALL_ESPI_SAF_SET_PROTECTION_REGIONS 279
#define K_SYSCALL_ESPI_SEND_OOB 280
#define K_SYSCALL_ESPI_SEND_VWIRE 281
#define K_SYSCALL_ESPI_WRITE_FLASH 282
#define K_SYSCALL_ESPI_WRITE_LPC_REQUEST 283
#define K_SYSCALL_ESPI_WRITE_REQUEST 284
#define K_SYSCALL_FLASH_ERASE 285
#define K_SYSCALL_FLASH_EX_OP 286
#define K_SYSCALL_FLASH_GET_PAGE_COUNT 287
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_IDX 288
#define K_SYSCALL_FLASH_GET_PAGE_INFO_BY_OFFS 289
#define K_SYSCALL_FLASH_GET_PARAMETERS 290
#define K_SYSCALL_FLASH_GET_WRITE_BLOCK_SIZE 291
#define K_SYSCALL_FLASH_READ 292
#define K_SYSCALL_FLASH_READ_JEDEC_ID 293
#define K_SYSCALL_FLASH_SFDP_READ 294
#define K_SYSCALL_FLASH_SIMULATOR_GET_MEMORY 295
#define K_SYSCALL_FLASH_WRITE 296
#define K_SYSCALL_FUEL_GAUGE_BATTERY_CUTOFF 297
#define K_SYSCALL_FUEL_GAUGE_GET_BUFFER_PROP 298
#define K_SYSCALL_FUEL_GAUGE_GET_PROP 299
#define K_SYSCALL_FUEL_GAUGE_GET_PROPS 300
#define K_SYSCALL_FUEL_GAUGE_SET_PROP 301
#define K_SYSCALL_FUEL_GAUGE_SET_PROPS 302
#define K_SYSCALL_GNSS_GET_ENABLED_SYSTEMS 303
#define K_SYSCALL_GNSS_GET_FIX_RATE 304
#define K_SYSCALL_GNSS_GET_NAVIGATION_MODE 305
#define K_SYSCALL_GNSS_GET_PERIODIC_CONFIG 306
#define K_SYSCALL_GNSS_GET_SUPPORTED_SYSTEMS 307
#define K_SYSCALL_GNSS_SET_ENABLED_SYSTEMS 308
#define K_SYSCALL_GNSS_SET_FIX_RATE 309
#define K_SYSCALL_GNSS_SET_NAVIGATION_MODE 310
#define K_SYSCALL_GNSS_SET_PERIODIC_CONFIG 311
#define K_SYSCALL_HWINFO_CLEAR_RESET_CAUSE 312
#define K_SYSCALL_HWINFO_GET_DEVICE_ID 313
#define K_SYSCALL_HWINFO_GET_RESET_CAUSE 314
#define K_SYSCALL_HWINFO_GET_SUPPORTED_RESET_CAUSE 315
#define K_SYSCALL_HWSPINLOCK_GET_MAX_ID 316
#define K_SYSCALL_HWSPINLOCK_LOCK 317
#define K_SYSCALL_HWSPINLOCK_TRYLOCK 318
#define K_SYSCALL_HWSPINLOCK_UNLOCK 319
#define K_SYSCALL_I2C_CONFIGURE 320
#define K_SYSCALL_I2C_GET_CONFIG 321
#define K_SYSCALL_I2C_RECOVER_BUS 322
#define K_SYSCALL_I2C_TARGET_DRIVER_REGISTER 323
#define K_SYSCALL_I2C_TARGET_DRIVER_UNREGISTER 324
#define K_SYSCALL_I2C_TRANSFER 325
#define K_SYSCALL_I2S_BUF_READ 326
#define K_SYSCALL_I2S_BUF_WRITE 327
#define K_SYSCALL_I2S_CONFIGURE 328
#define K_SYSCALL_I2S_TRIGGER 329
#define K_SYSCALL_I3C_DO_CCC 330
#define K_SYSCALL_I3C_TRANSFER 331
#define K_SYSCALL_IPM_COMPLETE 332
#define K_SYSCALL_IPM_MAX_DATA_SIZE_GET 333
#define K_SYSCALL_IPM_MAX_ID_VAL_GET 334
#define K_SYSCALL_IPM_SEND 335
#define K_SYSCALL_IPM_SET_ENABLED 336
#define K_SYSCALL_IVSHMEM_ENABLE_INTERRUPTS 337
#define K_SYSCALL_IVSHMEM_GET_ID 338
#define K_SYSCALL_IVSHMEM_GET_MAX_PEERS 339
#define K_SYSCALL_IVSHMEM_GET_MEM 340
#define K_SYSCALL_IVSHMEM_GET_OUTPUT_MEM_SECTION 341
#define K_SYSCALL_IVSHMEM_GET_PROTOCOL 342
#define K_SYSCALL_IVSHMEM_GET_RW_MEM_SECTION 343
#define K_SYSCALL_IVSHMEM_GET_STATE 344
#define K_SYSCALL_IVSHMEM_GET_VECTORS 345
#define K_SYSCALL_IVSHMEM_INT_PEER 346
#define K_SYSCALL_IVSHMEM_REGISTER_HANDLER 347
#define K_SYSCALL_IVSHMEM_SET_STATE 348
#define K_SYSCALL_KSCAN_CONFIG 349
#define K_SYSCALL_KSCAN_DISABLE_CALLBACK 350
#define K_SYSCALL_KSCAN_ENABLE_CALLBACK 351
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_IN_GET 352
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_BACKING_STORE_PAGE_OUT_GET 353
#define K_SYSCALL_K_MEM_PAGING_HISTOGRAM_EVICTION_GET 354
#define K_SYSCALL_K_MEM_PAGING_STATS_GET 355
#define K_SYSCALL_K_MEM_PAGING_THREAD_STATS_GET 356
#define K_SYSCALL_LED_BLINK 357
#define K_SYSCALL_LED_GET_INFO 358
#define K_SYSCALL_LED_OFF 359
#define K_SYSCALL_LED_ON 360
#define K_SYSCALL_LED_SET_BRIGHTNESS 361
#define K_SYSCALL_LED_SET_CHANNEL 362
#define K_SYSCALL_LED_SET_COLOR 363
#define K_SYSCALL_LED_WRITE_CHANNELS 364
#define K_SYSCALL_MAXIM_DS3231_GET_SYNCPOINT 365
#define K_SYSCALL_MAXIM_DS3231_REQ_SYNCPOINT 366
#define K_SYSCALL_MDIO_BUS_DISABLE 367
#define K_SYSCALL_MDIO_BUS_ENABLE 368
#define K_SYSCALL_MDIO_READ 369
#define K_SYSCALL_MDIO_READ_C45 370
#define K_SYSCALL_MDIO_WRITE 371
#define K_SYSCALL_MDIO_WRITE_C45 372
#define K_SYSCALL_NET_ADDR_NTOP 373
#define K_SYSCALL_NET_ADDR_PTON 374
#define K_SYSCALL_NET_ETH_GET_PTP_CLOCK_BY_INDEX 375
#define K_SYSCALL_NET_IF_GET_BY_INDEX 376
#define K_SYSCALL_NET_IF_IPV4_ADDR_ADD_BY_INDEX 377
#define K_SYSCALL_NET_IF_IPV4_ADDR_LOOKUP_BY_INDEX 378
#define K_SYSCALL_NET_IF_IPV4_ADDR_RM_BY_INDEX 379
#define K_SYSCALL_NET_IF_IPV4_SET_GW_BY_INDEX 380
#define K_SYSCALL_NET_IF_IPV4_SET_NETMASK_BY_INDEX 381
#define K_SYSCALL_NET_IF_IPV6_ADDR_ADD_BY_INDEX 382
#define K_SYSCALL_NET_IF_IPV6_ADDR_LOOKUP_BY_INDEX 383
#define K_SYSCALL_NET_IF_IPV6_ADDR_RM_BY_INDEX 384
#define K_SYSCALL_NET_SOCKET_SERVICE_REGISTER 385
#define K_SYSCALL_NRF_QSPI_NOR_XIP_ENABLE 386
#define K_SYSCALL_PECI_CONFIG 387
#define K_SYSCALL_PECI_DISABLE 388
#define K_SYSCALL_PECI_ENABLE 389
#define K_SYSCALL_PECI_TRANSFER 390
#define K_SYSCALL_PHY_CONFIGURE_LINK 391
#define K_SYSCALL_PHY_GET_LINK_STATE 392
#define K_SYSCALL_PHY_LINK_CALLBACK_SET 393
#define K_SYSCALL_PHY_READ 394
#define K_SYSCALL_PHY_WRITE 395
#define K_SYSCALL_PS2_CONFIG 396
#define K_SYSCALL_PS2_DISABLE_CALLBACK 397
#define K_SYSCALL_PS2_ENABLE_CALLBACK 398
#define K_SYSCALL_PS2_READ 399
#define K_SYSCALL_PS2_WRITE 400
#define K_SYSCALL_PTP_CLOCK_GET 401
#define K_SYSCALL_PWM_CAPTURE_CYCLES 402
#define K_SYSCALL_PWM_DISABLE_CAPTURE 403
#define K_SYSCALL_PWM_ENABLE_CAPTURE 404
#define K_SYSCALL_PWM_GET_CYCLES_PER_SEC 405
#define K_SYSCALL_PWM_SET_CYCLES 406
#define K_SYSCALL_RESET_LINE_ASSERT 407
#define K_SYSCALL_RESET_LINE_DEASSERT 408
#define K_SYSCALL_RESET_LINE_TOGGLE 409
#define K_SYSCALL_RESET_STATUS 410
#define K_SYSCALL_RETAINED_MEM_CLEAR 411
#define K_SYSCALL_RETAINED_MEM_READ 412
#define K_SYSCALL_RETAINED_MEM_SIZE 413
#define K_SYSCALL_RETAINED_MEM_WRITE 414
#define K_SYSCALL_RTC_ALARM_GET_SUPPORTED_FIELDS 415
#define K_SYSCALL_RTC_ALARM_GET_TIME 416
#define K_SYSCALL_RTC_ALARM_IS_PENDING 417
#define K_SYSCALL_RTC_ALARM_SET_CALLBACK 418
#define K_SYSCALL_RTC_ALARM_SET_TIME 419
#define K_SYSCALL_RTC_GET_CALIBRATION 420
#define K_SYSCALL_RTC_GET_TIME 421
#define K_SYSCALL_RTC_SET_CALIBRATION 422
#define K_SYSCALL_RTC_SET_TIME 423
#define K_SYSCALL_RTC_UPDATE_SET_CALLBACK 424
#define K_SYSCALL_RTIO_CQE_COPY_OUT 425
#define K_SYSCALL_RTIO_CQE_GET_MEMPOOL_BUFFER 426
#define K_SYSCALL_RTIO_RELEASE_BUFFER 427
#define K_SYSCALL_RTIO_SQE_CANCEL 428
#define K_SYSCALL_RTIO_SQE_COPY_IN_GET_HANDLES 429
#define K_SYSCALL_RTIO_SUBMIT 430
#define K_SYSCALL_SDHC_CARD_BUSY 431
#define K_SYSCALL_SDHC_CARD_PRESENT 432
#define K_SYSCALL_SDHC_DISABLE_INTERRUPT 433
#define K_SYSCALL_SDHC_ENABLE_INTERRUPT 434
#define K_SYSCALL_SDHC_EXECUTE_TUNING 435
#define K_SYSCALL_SDHC_GET_HOST_PROPS 436
#define K_SYSCALL_SDHC_HW_RESET 437
#define K_SYSCALL_SDHC_REQUEST 438
#define K_SYSCALL_SDHC_SET_IO 439
#define K_SYSCALL_SIP_SUPERVISORY_CALL 440
#define K_SYSCALL_SIP_SVC_PLAT_ASYNC_RES_REQ 441
#define K_SYSCALL_SIP_SVC_PLAT_ASYNC_RES_RES 442
#define K_SYSCALL_SIP_SVC_PLAT_FORMAT_TRANS_ID 443
#define K_SYSCALL_SIP_SVC_PLAT_FREE_ASYNC_MEMORY 444
#define K_SYSCALL_SIP_SVC_PLAT_FUNC_ID_VALID 445
#define K_SYSCALL_SIP_SVC_PLAT_GET_ERROR_CODE 446
#define K_SYSCALL_SIP_SVC_PLAT_GET_TRANS_IDX 447
#define K_SYSCALL_SIP_SVC_PLAT_UPDATE_TRANS_ID 448
#define K_SYSCALL_SMBUS_BLOCK_PCALL 449
#define K_SYSCALL_SMBUS_BLOCK_READ 450
#define K_SYSCALL_SMBUS_BLOCK_WRITE 451
#define K_SYSCALL_SMBUS_BYTE_DATA_READ 452
#define K_SYSCALL_SMBUS_BYTE_DATA_WRITE 453
#define K_SYSCALL_SMBUS_BYTE_READ 454
#define K_SYSCALL_SMBUS_BYTE_WRITE 455
#define K_SYSCALL_SMBUS_CONFIGURE 456
#define K_SYSCALL_SMBUS_GET_CONFIG 457
#define K_SYSCALL_SMBUS_HOST_NOTIFY_REMOVE_CB 458
#define K_SYSCALL_SMBUS_PCALL 459
#define K_SYSCALL_SMBUS_QUICK 460
#define K_SYSCALL_SMBUS_SMBALERT_REMOVE_CB 461
#define K_SYSCALL_SMBUS_WORD_DATA_READ 462
#define K_SYSCALL_SMBUS_WORD_DATA_WRITE 463
#define K_SYSCALL_SPI_RELEASE 464
#define K_SYSCALL_SPI_TRANSCEIVE 465
#define K_SYSCALL_SYSCON_GET_BASE 466
#define K_SYSCALL_SYSCON_GET_SIZE 467
#define K_SYSCALL_SYSCON_READ_REG 468
#define K_SYSCALL_SYSCON_WRITE_REG 469
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_AND_INVD_RANGE 470
#define K_SYSCALL_SYS_CACHE_DATA_FLUSH_RANGE 471
#define K_SYSCALL_SYS_CACHE_DATA_INVD_RANGE 472
#define K_SYSCALL_SYS_CSRAND_GET 473
#define K_SYSCALL_SYS_RAND32_GET 474
#define K_SYSCALL_SYS_RAND_GET 475
#define K_SYSCALL_TGPIO_PIN_CONFIG_EXT_TIMESTAMP 476
#define K_SYSCALL_TGPIO_PIN_DISABLE 477
#define K_SYSCALL_TGPIO_PIN_PERIODIC_OUTPUT 478
#define K_SYSCALL_TGPIO_PIN_READ_TS_EC 479
#define K_SYSCALL_TGPIO_PORT_GET_CYCLES_PER_SECOND 480
#define K_SYSCALL_TGPIO_PORT_GET_TIME 481
#define K_SYSCALL_UART_MUX_FIND 482
#define K_SYSCALL_UPDATEHUB_AUTOHANDLER 483
#define K_SYSCALL_UPDATEHUB_CONFIRM 484
#define K_SYSCALL_UPDATEHUB_PROBE 485
#define K_SYSCALL_UPDATEHUB_REBOOT 486
#define K_SYSCALL_UPDATEHUB_UPDATE 487
#define K_SYSCALL_USER_FAULT 488
#define K_SYSCALL_W1_CHANGE_BUS_LOCK 489
#define K_SYSCALL_W1_CONFIGURE 490
#define K_SYSCALL_W1_GET_SLAVE_COUNT 491
#define K_SYSCALL_W1_READ_BIT 492
#define K_SYSCALL_W1_READ_BLOCK 493
#define K_SYSCALL_W1_READ_BYTE 494
#define K_SYSCALL_W1_RESET_BUS 495
#define K_SYSCALL_W1_SEARCH_BUS 496
#define K_SYSCALL_W1_WRITE_BIT 497
#define K_SYSCALL_W1_WRITE_BLOCK 498
#define K_SYSCALL_W1_WRITE_BYTE 499
#define K_SYSCALL_WDT_DISABLE 500
#define K_SYSCALL_WDT_FEED 501
#define K_SYSCALL_WDT_SETUP 502
#define K_SYSCALL_ZSOCK_ACCEPT 503
#define K_SYSCALL_ZSOCK_BIND 504
#define K_SYSCALL_ZSOCK_CLOSE 505
#define K_SYSCALL_ZSOCK_CONNECT 506
#define K_SYSCALL_ZSOCK_FCNTL 507
#define K_SYSCALL_ZSOCK_GETHOSTNAME 508
#define K_SYSCALL_ZSOCK_GETPEERNAME 509
#define K_SYSCALL_ZSOCK_GETSOCKNAME 510
#define K_SYSCALL_ZSOCK_GETSOCKOPT 511
#define K_SYSCALL_ZSOCK_GET_CONTEXT_OBJECT 512
#define K_SYSCALL_ZSOCK_INET_PTON 513
#define K_SYSCALL_ZSOCK_IOCTL 514
#define K_SYSCALL_ZSOCK_LISTEN 515
#define K_SYSCALL_ZSOCK_POLL 516
#define K_SYSCALL_ZSOCK_RECVFROM 517
#define K_SYSCALL_ZSOCK_SELECT 518
#define K_SYSCALL_ZSOCK_SENDMSG 519
#define K_SYSCALL_ZSOCK_SENDTO 520
#define K_SYSCALL_ZSOCK_SETSOCKOPT 521
#define K_SYSCALL_ZSOCK_SHUTDOWN 522
#define K_SYSCALL_ZSOCK_SOCKET 523
#define K_SYSCALL_ZSOCK_SOCKETPAIR 524
#define K_SYSCALL_Z_ERRNO 525
#define K_SYSCALL_Z_ZSOCK_GETADDRINFO_INTERNAL 526


#ifndef _ASMLANGUAGE

#include <stdarg.h>
#include <stdint.h>

#endif /* _ASMLANGUAGE */

#endif /* ZEPHYR_SYSCALL_LIST_H */
