/*
 * hdf_mac80211_sta_event.h
 *
 * hdf driver
 *
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */
#ifndef WAL_MAC80211_STA_EVENT_H_
#define WAL_MAC80211_STA_EVENT_H_

#define HDF_ETHER_ADDR_LEN (6)
#include <net/cfg80211.h>

typedef struct _HdfConnetResult {
    uint8_t   bssid[HDF_ETHER_ADDR_LEN];  /**< MAC address of the AP associated with the station */
    uint16_t  statusCode;           /**< 16-bit status code defined in the IEEE protocol */
    uint8_t  *rspIe;                /**< Association response IE */
    uint8_t  *reqIe;                /**< Association request IE */
    uint32_t  reqIeLen;             /**< Length of the association request IE */
    uint32_t  rspIeLen;             /**< Length of the association response IE */
    uint16_t  connectStatus;        /**< Connection status */
    uint16_t  freq;                 /**< Frequency of the AP */
} HdfConnetResult;

typedef enum {
    HDF_WIFI_SCAN_SUCCESS,
    HDF_WIFI_SCAN_FAILED,
    HDF_WIFI_SCAN_REFUSED,
    HDF_WIFI_SCAN_TIMEOUT
} HdfWifiScanStatus;
extern int32_t HdfScanEventCallback(struct net_device *ndev, HdfWifiScanStatus _status);
extern int32_t HdfDisconnectedEventCallback(struct net_device *ndev, uint16_t reason, uint8_t *ie, uint32_t len);
extern void HdfInformBssFrameEventCallback(struct net_device *ndev, struct ieee80211_channel *channel, int32_t signal,
    int16_t freq, struct ieee80211_mgmt *mgmt, uint32_t mgmtLen);
extern int32_t HdfConnectResultEventCallback(struct net_device *ndev, uint8_t *bssid, uint8_t *reqIe,
    uint8_t *rspIe, uint32_t reqIeLen, uint32_t rspIeLen, uint16_t connectStatus, uint16_t freq);
void WifiScanFree(struct cfg80211_scan_request **request);
#endif

