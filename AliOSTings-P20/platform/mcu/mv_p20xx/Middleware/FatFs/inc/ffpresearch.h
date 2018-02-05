/**
 *******************************************************************************
 * @file    ffpresearch.h
 * @author  Castle
 * @version V0.1.0
 * @date    24-August-2017
 * @brief
 * @maintainer Castle
 *******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, MVSILICON SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2013 MVSilicon </center></h2>
 */
#ifndef _FFPRESEARCH_H_
#define _FFPRESEARCH_H_

/**
 * Refer to Audio Decoder Type Set
 */
typedef enum _FileType
{
	FILE_TYPE_UNKOWN               = 0,       /**< Unknown decoder                     */
	FILE_TYPE_PURE_SOFTWARE_DECODERS       = 1,       /**< Pure software decoders as follows   */
	FILE_TYPE_WAV,                            /**< WAV  decoder */
	FILE_TYPE_FLAC,                           /**< FLAC decoder */
	FILE_TYPE_AAC,                            /**< AAC  decoder */
	FILE_TYPE_AIF,                            /**< AIFF and AIFC decoder */
	FILE_TYPE_AMR,                            /**< AMR  decoder */
	FILE_TYPE_WITH_HARDWARE_DECODERS       = 128,     /**< Decoders with hardware as follows   */
	FILE_TYPE_MP3,                            /**< MP3  decoder */
	FILE_TYPE_WMA,                            /**< WAM  decoder */
	FILE_TYPE_SBC,                            /**< SBC  decoder */
	FILE_TYPE_MSBC,                           /**< mSBC decoder */
} FileType;



typedef struct _ff_presearch_node
{
	FATFS*	fs;
	WORD	id;
	DWORD	sclust;
	FSIZE_t	objsize;
	DWORD	dir_sect;
	TCHAR	altname[13];
#if FF_FS_EXFAT
	DWORD	c_ofs;
	BYTE	stat;
#endif
	BYTE	file_type;
} ff_presearch_node;

FRESULT f_scan_vol(char *volume);

FRESULT f_open_by_num(FIL *filehandle, UINT number);

FileType f_audio_get_type(UINT number);

UINT f_file_count_in_node(void);

#endif

