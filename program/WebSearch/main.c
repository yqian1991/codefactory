#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <assert.h>

#ifdef ERROR
#undef ERROR
#endif

#define U8 unsigned char
#define U32 unsigned int
#define STATUS unsigned int

#define OK 0
#define ERROR (~0L)
#define MAX_BLOCK_SIZE 1024
#define MAX_DOMAIN_NAME_LENGTH 64
#define MAX_THREAD_NUMBER (8)

#pragma comment(lib, "wininet.lib")
static STATUS download_web_page(const char* url, const char* path);

static int end = 0;
static int front = 1;
static HANDLE h_index;

/* index to read html file */
static int get_read_index()
{
	int index;

	WaitForSingleObject(h_index, INFINITE);
	if(end == front)
	{
		ReleaseSemaphore(h_index, 1, NULL);
		return -1;
	}

	index = end ++;
	ReleaseSemaphore(h_index, 1, NULL);
	return index;
}

/* index to write html file */
static int get_write_index()
{
	int index;

	WaitForSingleObject(h_index, INFINITE);
	index = front ++;
	ReleaseSemaphore(h_index, 1, NULL);
	return index;
}

/* get length of html file */
static int get_file_size(const char* path)
{
	HANDLE hFile;
	int size = 0;

	hFile = CreateFile(path, FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE)
    {
		size = GetFileSize(hFile, NULL);
        CloseHandle(hFile);
    }

	return size;
}

/* get all data from html file */
static STATUS get_file_content(const char* path, void** pp_buffer, int* size)
{
	int length;
	char* buffer;
	HANDLE hFile;

	if(NULL == path)
	{
		return ERROR;
	}

	if(NULL == pp_buffer)
	{
		return ERROR;
	}

	if(NULL == size)
	{
		return ERROR;
	}

	length = get_file_size(path);
	if(0 == length)
	{
		return ERROR;
	}

	buffer = (char*) malloc(length +1);
	if(NULL == buffer)
	{
		return ERROR;
	}

	buffer[length] = '\0';
	hFile = fopen(path, "r+b");
	if(NULL == hFile)
	{
		free(buffer);
		return ERROR;
	}

	fread(buffer, 1, length, hFile);
	fclose(hFile);

	*pp_buffer = buffer;
	*size = length;
	return OK;
}

/* show all http name, sometimes just for debug use */
static void print_http_name(const char* buffer, int size)
{
	while(size --)
	{
		printf("%c", *buffer ++);
	}

	printf("\n");
}


static void download_linked_page(const char* url, int size)
{
	char* data;
	char name[64];

	print_http_name(url, size);
	data = (char*)malloc(size + 1);
	if(NULL == data)
	{
		return;
	}

	data[size] = '\0';
	memmove(data, url, size);
	memset(name, 0, 64);
	sprintf(name, "E:/download/%d.html", get_write_index());
	download_web_page(data, name);

	/*  free data memroy, which contained http domain name */
	free(data);
}

/* get http form html file, then download it by its name*/
static void get_http_and_download(const char* buffer)
{
	const char* prev;
	const char* next;
	char letter;
	int count;

	if(NULL == buffer)
	{
		return;
	}

	next = buffer;
	while(1)
	{
		next = strstr(next, "http://");
		if(NULL == next)
		{
			break;
		}

		count = MAX_DOMAIN_NAME_LENGTH;
		prev = next;
		next += strlen("http://");

		while(1)
		{
			if(!count)
			{
				break;
			}

			count --;
			letter = *next;
			if('"' == letter || '\'' == letter || ')' ==  letter || '>' == letter)
			{
				break;
			}

			next ++;
		}

		if(count)
		{
			download_linked_page(prev, next - prev);
		}
	}

}

/* implement page download */
static STATUS download_web_page(const char* url, const char* path)
{
	U8 buffer[MAX_BLOCK_SIZE];
	U32 iNumber;
	FILE* hFile;
	HINTERNET hSession;
	HINTERNET hUrl;
	STATUS result;

	hSession = InternetOpen("RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(NULL == hSession)
	{
		return ERROR;
	}

	hUrl = InternetOpenUrl(hSession, url, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
	if(NULL == hUrl)
	{
		result = ERROR;
		goto error1;
	}

	hFile = fopen(path, "wb");
	if(NULL == hFile)
	{
		result = ERROR;
		goto error2;
	}

	iNumber = 1;
	while(iNumber > 0)
	{
		InternetReadFile(hUrl, buffer, MAX_BLOCK_SIZE -1, &iNumber);
		fwrite(buffer, sizeof(char), iNumber, hFile);
	}

	fclose(hFile);
	result = OK;

error2:
	InternetCloseHandle(hUrl);

error1:
	InternetCloseHandle(hSession);

	return result;
}

/* download page and its linked pages */
DWORD WINAPI download_page_entry(LPVOID param)
{
	char* buffer;
	int size;
	char name[64];
	int index;

	while(1)
	{
		while( -1 == (index = get_read_index()))
		{
			Sleep(100);
		}

		memset(name, 0, 64);
		sprintf(name, "E:/download/%d.html", index);
		if(OK == get_file_content(name, &buffer, &size))
		{
			get_http_and_download(buffer);
			free(buffer);
		}
	}
}

/* entry of programme */
int main(int argc, char* argv[])
{
	int index;
	HANDLE h_download[MAX_THREAD_NUMBER];

	h_index = CreateSemaphore(NULL, 1, 1, NULL);
	if(NULL == h_index)
	{
		assert(0);
	}

	/* 0.html is just the start page */
	download_web_page("http://book.dangdang.com", "E:/download/0.html");
	for(index = 0; index < MAX_THREAD_NUMBER; index ++)
	{
		h_download[index] = CreateThread(NULL, 0, download_page_entry, 0, 0, NULL);
		if(NULL == h_download[index])
		{
			assert(0);
		}
	}

	WaitForMultipleObjects(MAX_THREAD_NUMBER, h_download, TRUE, INFINITE);
	CloseHandle(h_index);
	return 1;
}
