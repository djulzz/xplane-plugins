/**
 * @file arin429_TestMessages.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ARINC429_TESTMESSAGES_HPP
#define ARINC429_TESTMESSAGES_HPP

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* 10 MS MESSAGES */
#define MSG_10_MS_001   001
#define MSG_10_MS_002   002
#define MSG_10_MS_003   003
#define MSG_10_MS_004   004
#define MSG_10_MS_005   005
#define MSG_10_MS_006   006
#define MSG_10_MS_007   007
#define MSG_10_MS_008   010
#define MSG_10_MS_009   011
#define MSG_10_MS_010   012

#define MSG_10_MS_011   013
#define MSG_10_MS_012   014
#define MSG_10_MS_013   015
#define MSG_10_MS_014   016
#define MSG_10_MS_015   017
#define MSG_10_MS_016   020
#define MSG_10_MS_017   021
#define MSG_10_MS_018   022
#define MSG_10_MS_019   023
#define MSG_10_MS_020   024

#define MSG_10_MS_021   025
#define MSG_10_MS_022   026
#define MSG_10_MS_023   027
#define MSG_10_MS_024   030
#define MSG_10_MS_025   031
#define MSG_10_MS_026   032
#define MSG_10_MS_027   033
#define MSG_10_MS_028   034
#define MSG_10_MS_029   035
#define MSG_10_MS_030   036
#define MSG_10_MS_031   037

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* 30 MS MESSAGES */
#define MSG_30_MS_001   040
#define MSG_30_MS_002   041
#define MSG_30_MS_003   042
#define MSG_30_MS_004   043
#define MSG_30_MS_005   044
#define MSG_30_MS_006   045
#define MSG_30_MS_007   046
#define MSG_30_MS_008   047
#define MSG_30_MS_009   050
#define MSG_30_MS_010   051

#define MSG_30_MS_011   052
#define MSG_30_MS_012   053
#define MSG_30_MS_013   054
#define MSG_30_MS_014   055
#define MSG_30_MS_015   056
#define MSG_30_MS_016   057
#define MSG_30_MS_017   060
#define MSG_30_MS_018   061
#define MSG_30_MS_019   062
#define MSG_30_MS_020   063

#define MSG_30_MS_021   064
#define MSG_30_MS_022   065
#define MSG_30_MS_023   066
#define MSG_30_MS_024   067
#define MSG_30_MS_025   070
#define MSG_30_MS_026   071
#define MSG_30_MS_027   072
#define MSG_30_MS_028   073
#define MSG_30_MS_029   074
#define MSG_30_MS_030   075
#define MSG_30_MS_031   076

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* 60 MS MESSAGES */
#define MSG_60_MS_001   077
#define MSG_60_MS_002   0100
#define MSG_60_MS_003   0101
#define MSG_60_MS_004   0102
#define MSG_60_MS_005   0103
#define MSG_60_MS_006   0104
#define MSG_60_MS_007   0105
#define MSG_60_MS_008   0106
#define MSG_60_MS_009   0107
#define MSG_60_MS_010   0110

#define MSG_60_MS_011   0111
#define MSG_60_MS_012   0112
#define MSG_60_MS_013   0113
#define MSG_60_MS_014   0114
#define MSG_60_MS_015   0115
#define MSG_60_MS_016   0116
#define MSG_60_MS_017   0117
#define MSG_60_MS_018   0120
#define MSG_60_MS_019   0121
#define MSG_60_MS_020   0122

#define MSG_60_MS_021   0123
#define MSG_60_MS_022   0124
#define MSG_60_MS_023   0125
#define MSG_60_MS_024   0126
#define MSG_60_MS_025   0127
#define MSG_60_MS_026   0130
#define MSG_60_MS_027   0131
#define MSG_60_MS_028   0132
#define MSG_60_MS_029   0133
#define MSG_60_MS_030   0134
#define MSG_60_MS_031   0135

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* 240 MS MESSAGES */
#define MSG_240_MS_001   0136
#define MSG_240_MS_002   0137
#define MSG_240_MS_003   0140
#define MSG_240_MS_004   0141
#define MSG_240_MS_005   0142
#define MSG_240_MS_006   0143
#define MSG_240_MS_007   0144
#define MSG_240_MS_008   0145
#define MSG_240_MS_009   0146
#define MSG_240_MS_010   0147

#define MSG_240_MS_011   0150
#define MSG_240_MS_012   0151
#define MSG_240_MS_013   0152
#define MSG_240_MS_014   0153
#define MSG_240_MS_015   0154
#define MSG_240_MS_016   0155
#define MSG_240_MS_017   0156
#define MSG_240_MS_018   0157
#define MSG_240_MS_019   0160
#define MSG_240_MS_020   0161

#define MSG_240_MS_021   0162
#define MSG_240_MS_022   0163
#define MSG_240_MS_023   0164
#define MSG_240_MS_024   0165
#define MSG_240_MS_025   0166
#define MSG_240_MS_026   0167
#define MSG_240_MS_027   0170
#define MSG_240_MS_028   0171
#define MSG_240_MS_029   0172
#define MSG_240_MS_030  0173
#define MSG_240_MS_031  0174

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* NO OP MESSAGE */
#define MSG_NO_OP       0377

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* SDI HEADER/FOOTER */
#define SDI_OK  0
#define SDI_FAILURE 1

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* CONSTANTS */
#define BAE_PERIOD_MS   10
#define ALIVE_PERIOD_MS 1000
#define BUF_SIZE_1024   1024
#define MAX_COUNTER     1000
#define MS_TO_SEC       0.001

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/* MESSAGE PARAMETERS */
#define NUM_DIFFERENT_MESSAGES  20
#define NUM_MESSAGES_10_MS  4
#define NUM_MESSAGES_60_MS  2
#define NUM_MESSAGES_240_MS 14


#define DEFAULT_SIG_DIGITS  19
#define DEFAULT_END_BITS    28
#define DEFAULT_SIG_BITS    29
#define DEFAULT_RESOLUTION  0.006548

#endif /* ARINC429_TESTMESSAGES_HPP defined */