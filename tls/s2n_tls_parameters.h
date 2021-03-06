/*
 * Copyright 2014 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

/* Codes from http://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-5 */
#define TLS_NULL_WITH_NULL_NULL             0x00, 0x00
#define TLS_RSA_WITH_AES_256_CBC_SHA256     0x00, 0x3D
#define TLS_RSA_WITH_AES_256_CBC_SHA        0x00, 0x35
#define TLS_RSA_WITH_AES_128_CBC_SHA256     0x00, 0x3C
#define TLS_RSA_WITH_AES_128_CBC_SHA        0x00, 0x2F
#define TLS_RSA_WITH_3DES_EDE_CBC_SHA       0x00, 0x0A
#define TLS_RSA_WITH_RC4_128_MD5            0x00, 0x04
#define TLS_RSA_WITH_RC4_128_SHA            0x00, 0x05

#define TLS_DHE_RSA_WITH_AES_128_CBC_SHA    0x00, 0x33
#define TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 0x00, 0x67
#define TLS_DHE_RSA_WITH_AES_256_CBC_SHA    0x00, 0x39
#define TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 0x00, 0x6B
#define TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA   0x00, 0x16

#define TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA       0xC0, 0x13
#define TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256    0xC0, 0x27
#define TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA       0xC0, 0x14
#define TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384    0xC0, 0x28
#define TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA      0xC0, 0x12

#define TLS_RSA_WITH_AES_128_GCM_SHA256          0x00, 0x9C
#define TLS_RSA_WITH_AES_256_GCM_SHA384          0x00, 0x9D
#define TLS_DHE_RSA_WITH_AES_128_GCM_SHA256      0x00, 0x9E
#define TLS_DHE_RSA_WITH_AES_256_GCM_SHA384      0x00, 0x9F
#define TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256    0xC0, 0x2F
#define TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384    0xC0, 0x30

/* From https://tools.ietf.org/html/rfc7507 */
#define TLS_FALLBACK_SCSV                   0x56, 0x00
#define TLS_EMPTY_RENEGOTIATION_INFO_SCSV   0x00, 0xff

/* TLS extensions from https://www.iana.org/assignments/tls-extensiontype-values/tls-extensiontype-values.xhtml */
#define TLS_EXTENSION_SERVER_NAME           0
#define TLS_EXTENSION_STATUS_REQUEST        5
#define TLS_EXTENSION_ELLIPTIC_CURVES      10
#define TLS_EXTENSION_EC_POINT_FORMATS     11
#define TLS_EXTENSION_SIGNATURE_ALGORITHMS 13
#define TLS_EXTENSION_ALPN                 16
#define TLS_EXTENSION_RENEGOTIATION_INFO   65281

/* TLS signature algorithms */
#define TLS_SIGNATURE_ALGORITHM_RSA         1
#define TLS_HASH_ALGORITHM_MD5              1
#define TLS_HASH_ALGORITHM_SHA1             2
#define TLS_HASH_ALGORITHM_SHA224           3
#define TLS_HASH_ALGORITHM_SHA256           4
#define TLS_HASH_ALGORITHM_SHA384           5
#define TLS_HASH_ALGORITHM_SHA512           6

/* The TLS record types we support */
#define TLS_CHANGE_CIPHER_SPEC 20
#define TLS_ALERT              21
#define TLS_HANDSHAKE          22
#define TLS_APPLICATION_DATA   23

/* Elliptic cruves from https://www.iana.org/assignments/tls-parameters/tls-parameters.xhtml#tls-parameters-8 */
#define TLS_EC_CURVE_SECP_256_R1           23
#define TLS_EC_CURVE_SECP_384_R1           24

/* The maximum size of a TLS record is 16389 bytes. This is;  1 byte for content
 * type, 2 bytes for the protocol version, 2 bytes for the length field,
 * and then up to 2^14 for the encrypted+compressed payload data.
 */
#define S2N_TLS_RECORD_HEADER_LENGTH    5
#define S2N_TLS_MAXIMUM_FRAGMENT_LENGTH 16384
#define S2N_TLS_MAXIMUM_RECORD_LENGTH   (S2N_TLS_MAXIMUM_FRAGMENT_LENGTH + S2N_TLS_RECORD_HEADER_LENGTH)

/* The maximum size of an SSL2 message is 2^14 - 1, as neither of the first two
 * bits in the length field are usable. Per;
 * http://www-archive.mozilla.org/projects/security/pki/nss/ssl/draft02.html
 * section 1.1 
 */
#define S2N_SSL2_RECORD_HEADER_LENGTH   2
#define S2N_SSL2_MAXIMUM_MESSAGE_LENGTH 16383
#define S2N_SSL2_MAXIMUM_RECORD_LENGTH  (S2N_SSL2_MAXIMUM_MESSAGE_LENGTH + S2N_SSL2_RECORD_HEADER_LENGTH)

/* s2n can use a "small" record length that is aligned to the dominant internet MTU;
 * 1500 bytes, minus 20 bytes for an IP header, minus 20 bytes for a tcp
 * header and 20 bytes for tcp/ip options (timestamp, sack etc) and a "large" record
 * length that is designed to maximize throughput (fewer MACs per byte transferred
 * and better efficiency of crypto engines).
 */
#define S2N_SMALL_RECORD_LENGTH (1500 - 20 - 20 - 20)
#define S2N_SMALL_FRAGMENT_LENGTH (S2N_SMALL_RECORD_LENGTH - S2N_TLS_RECORD_HEADER_LENGTH)
#define S2N_LARGE_RECORD_LENGTH S2N_TLS_MAXIMUM_RECORD_LENGTH
#define S2N_LARGE_FRAGMENT_LENGTH S2N_TLS_MAXIMUM_FRAGMENT_LENGTH

/* Put a 64k cap on the size of any handshake message */
#define S2N_MAXIMUM_HANDSHAKE_MESSAGE_LENGTH (64 * 1024)

/* Alert messages are always 2 bytes long */
#define S2N_ALERT_LENGTH 2

/* Handshake messages have their own header too */
#define TLS_HANDSHAKE_HEADER_LENGTH   4
