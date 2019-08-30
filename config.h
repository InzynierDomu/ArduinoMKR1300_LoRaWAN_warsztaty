/**
 * @file config.h
 * @brief software configuration
 * @author by Szymon Markiewicz
 * @details  
 * @date 08-2019
 */

#ifndef CONFIG_H_
#define CONFIG_H_

const bool IS_OTAA = false;   ///< LoRaWAN authorization method, ABP or OTAA

/*OTAA credential*/
const String DEVEUI = "";     ///< Device EUI
const String APPEUI = "";     ///< Application EUI
const String APPKEY = "";     ///< Application key

/*ABP credential*/
const String DEVADDR ="";   ///< Device adress  
const String NWKSKEY ="";  ///< Network key
const String APPSKEY ="";  ///< Application session key

const int UPLINK_PORT = 2;   ///< Port for uplink

const int REPS_INTERVAL = 60000;   ///< Uplink interval in miliseconds

#endif /* CONFIG_H_ */
