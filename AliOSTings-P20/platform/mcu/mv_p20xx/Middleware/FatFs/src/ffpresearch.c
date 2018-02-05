/**
 *******************************************************************************
 * @file    ffpresearch.c
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

#include <stdio.h>
#include <string.h>
#include "type.h"


#include "diskio.h"
#include "ff.h"
#include "ffconf.h"
#include "integer.h"

#include "ffpresearch.h"


#define	DBG(format, ...)		printf(format, ##__VA_ARGS__)

#define IsUpper(c)	((c) >= 'A' && (c) <= 'Z')
#define IsLower(c)	((c) >= 'a' && (c) <= 'z')
#define IsDigit(c)	((c) >= '0' && (c) <= '9')


#define MAX_DIR_STACK_DEPTH 10
#define MAX_FILE_NODE 100

static DIR dirs_stack[MAX_DIR_STACK_DEPTH] = {0};
static char cur_full_path[250] = {"1:"};
static ff_presearch_node p_node[MAX_FILE_NODE] = {0};
static UINT node_index;
static FILINFO Finfo;

static void reset_node_index(void)
{
	node_index = 0;
}

static FileType get_audio_type(TCHAR *string)
{
	UINT len;

	len = strlen(string);
	while(--len)
	{
		if(string[len] == '.')
			break;
	}

	len ++;
	if (IsLower(string[len])) string[len] -= 0x20;
	if (IsLower(string[len + 1])) string[len + 1] -= 0x20;
	if (IsLower(string[len + 2])) string[len + 2] -= 0x20;
	if (IsLower(string[len + 3])) string[len + 3] -= 0x20;

	if((string[len + 0] == 'M') && (string[len + 1] == 'P') && (string[len + 2] == '3' || string[len + 2] == '2'))
	{
		return FILE_TYPE_MP3;
	}
	else if((string[len + 0] == 'W') && (string[len + 1] == 'M') && (string[len + 2] == 'A'))
	{
		return FILE_TYPE_WMA;
	}
	else if((string[len + 0] == 'A') && (string[len + 1] == 'S') && (string[len + 2] == 'F'))
	{
		return FILE_TYPE_WMA;
	}
	else if((string[len + 0] == 'W') && (string[len + 1] == 'M') && (string[len + 2] == 'V'))
	{
		return FILE_TYPE_WMA;
	}
	else if((string[len + 0] == 'A') && (string[len + 1] == 'S') && (string[len + 2] == 'X'))
	{
		return FILE_TYPE_WMA;
	}
	else if((string[len + 0] == 'W') && (string[len + 1] == 'A') && (string[len + 2] == 'V'))
	{
		return FILE_TYPE_WAV;
	}
	else if((string[len + 0] == 'S') && (string[len + 1] == 'B') && (string[len + 2] == 'C'))
	{
		return FILE_TYPE_SBC;
	}
	else if((string[len + 0] == 'F') && (string[len + 1] == 'L') && (string[len + 2] == 'A') && (string[len + 3] == 'C'))
	{
		return FILE_TYPE_FLAC;
	}
	else if(((string[len + 0] == 'A') && (string[len + 1] == 'A') && string[len + 2] == 'C')
			|| ((string[len + 0] == 'M') && (string[len + 1] == 'P') && string[len + 2] == '4')
			|| ((string[len + 0] == 'M') && (string[len + 1] == '4') && string[len + 2] == 'A'))
	{
		return FILE_TYPE_AAC;
	}
	else if((string[0] == 'A') && (string[len + 1] == 'I') && (string[len + 2] == 'F'))
	{
		return FILE_TYPE_AIF;
	}
	else
	{
		return FILE_TYPE_UNKOWN;
	}
}

static FRESULT store_filehandle_by_dir(DIR *current_dir, FILINFO *finfo)
{
	ff_presearch_node* cc_index;

	if(node_index > MAX_FILE_NODE - 1)
		return FR_TOO_MANY_OPEN_FILES;

	cc_index = &p_node[node_index];
	cc_index->fs = current_dir->obj.fs;//fs
	cc_index->id = current_dir->obj.id;//volume
	cc_index->sclust = finfo->fcl;//first cluster
	cc_index->objsize = finfo->fsize;
	cc_index->dir_sect = current_dir->sect;
	memcpy(cc_index->altname, finfo->altname, 13);
#if FF_FS_EXFAT
	if(cc_index->fs->fs_type == FS_EXFAT)
	{
		cc_index->c_ofs = current_dir->blk_ofs;
		cc_index->stat = finfo->stat & 2;
	}
#endif
	cc_index->file_type = get_audio_type(finfo->fname);

	//DBG("Store file info ok, current index: %d, file_type=%d\n", node_index, cc_index->file_type);
	node_index ++;
	return FR_OK;
}

FileType f_audio_get_type(UINT number)
{
	if(number > MAX_FILE_NODE - 1 || number >= node_index)
		return FILE_TYPE_UNKOWN;

	return (FileType)p_node[number].file_type;
}


FRESULT f_open_by_num(FIL *filehandle, UINT number)
{
	ff_presearch_node* cc_index;

	if(number > MAX_FILE_NODE - 1 || number >= node_index)
		return FR_NO_FILE;

	cc_index = &p_node[number];
	memset(filehandle, 0x00, sizeof(FIL));

	filehandle->obj.fs = cc_index->fs;
	filehandle->obj.id = cc_index->id;
	//filehandle->obj.attr = 0;
	//filehandle->obj.stat = 0;
	filehandle->obj.sclust = cc_index->sclust;
	filehandle->obj.objsize = cc_index->objsize;
	filehandle->flag = FA_READ;
	//filehandle->err = 0;
	//filehandle->fptr = 0;
	//filehandle->clust = 0;
	//filehandle->sect = 0;
	filehandle->dir_sect = cc_index->dir_sect;
	filehandle->dir_ptr = NULL;//
#if FF_FS_EXFAT
	if(cc_index->fs->fs_type == FS_EXFAT)
	{
		//filehandle->obj.n_cont = 0;
		//filehandle->obj.n_frag = 0;
		//filehandle->obj.c_scl = 0;
		//filehandle->obj.c_size = 0;
		filehandle->obj.c_ofs = cc_index->c_ofs;

		filehandle->obj.stat = cc_index->stat;
	}
#endif
	return FR_OK;
}

UINT f_file_count_in_node(void)
{
	return node_index;
}

void list_all_file_in_node(void)
{
	UINT i;
	for(i = 0; i < node_index; i++)
	{
		DBG("%03d-->%s\n", i, p_node[i].altname);
	}
}

/**
 * @brief
 *
 * @param	volume : "1:/"
 * @return
 *
 * ERRORS
 *
 * @note
 */
//FIL fileSh;
FRESULT f_scan_vol(char *volume)
{
	FRESULT res;
	bool goback, need_open_dir = TRUE;
	BYTE cur_dir_depth = 0, file_sum = 0, dir_sum = 0;
	DIR temp_dir;

	f_chdrive(volume);
	memset(cur_full_path, 0x00, sizeof(cur_full_path));
	memset(&dirs_stack[0], 0x00, sizeof(DIR)*MAX_DIR_STACK_DEPTH);
	reset_node_index();

	while(1)
	{
		//first time to open this dir; else, read the rest dirs
		if (need_open_dir)
		{
			DIR *cDir = &dirs_stack[cur_dir_depth];
			//DBG("entry a new dir->%s\n", cur_full_path);
			f_chdir(cur_full_path);
			if((res = f_opendir(&dirs_stack[cur_dir_depth], ".")) != FR_OK)
			{
				DBG("f_opendir failed: %s\n", cur_full_path);
				break;
			}
			memcpy(&temp_dir, &dirs_stack[cur_dir_depth], sizeof(DIR));

			//FIRST STEP : to search files
			while (((res = f_readdir(&dirs_stack[cur_dir_depth], &Finfo)) == FR_OK) && Finfo.fname[0])
			{
				if (Finfo.fattrib & AM_ARC)
				{
					//save file info to open by number
					//store_filehandle_by_dir(cDir, &Finfo);

					if(get_audio_type(Finfo.fname) !=  FILE_TYPE_UNKOWN)
					{
						//DBG("FILE->%s/%s\n", cur_full_path, Finfo.fname);
						store_filehandle_by_dir(cDir, &Finfo);
					}
					/*
					memset(&fileSh, 0x00, sizeof(FIL));
					if(f_open(&fileSh, "abc.mp3", FA_READ) == RES_OK)
					{
						DBG("open OK!\n");
						f_close(&fileSh);
					}
					*/
					file_sum++;
				}
			}
			//re-open dir to start a new search for son-dir
			memcpy(&dirs_stack[cur_dir_depth], &temp_dir, sizeof(DIR));

			dir_sum++;
		}

		goback = TRUE;
		//SECOND STEP : to search dirs and entry
		//THREE result:
		//1. encounter a sub-dir, go into it
		//2. reach the END of dir, goback
		//3. reach the max depth, goback
		while (((res = f_readdir(&dirs_stack[cur_dir_depth], &Finfo)) == FR_OK) && Finfo.fname[0])
		{
			if (Finfo.fattrib & AM_DIR)
			{
				//son-dir, prepare to entry it
				if(cur_dir_depth < MAX_DIR_STACK_DEPTH - 1)
				{
					BYTE pLen;
					if((pLen = strlen(cur_full_path)) > sizeof(cur_full_path) - strlen(Finfo.fname) - 1)
					{
						DBG("full path too long!!!\n");
						return FR_NO_PATH;
					}
					*(cur_full_path + pLen) = '/';
					strcpy(cur_full_path + pLen + 1, Finfo.fname);
					cur_dir_depth++;
					need_open_dir = TRUE;
					goback = FALSE;
				}
				else
				{
					//if reach the max depth, just go back and not to read rest dirs
					DBG("Reach max dir depth, go back.\n");
					need_open_dir = FALSE;
					goback = TRUE;
				}
				break;
			}
		}

		//goback to the previous level
		if(goback)
		{
			if(cur_dir_depth)
			{
				BYTE index = strlen(cur_full_path);
				cur_dir_depth--;
				need_open_dir = FALSE;
				while(--index && cur_full_path[index] != '/');
				cur_full_path[index] = '\0';
			}
			else
			{
				DBG("Finished all searching!\n");
				break;//finished all, break the while(1)
			}
			//DBG("GoBack to previous level.\n");
		}
	}

	DBG("Dir sum = %d.\n", dir_sum);
	DBG("File sum = %d.\n", file_sum);
	DBG("Song File sum = %d.\n", f_file_count_in_node());
	return res;
}



