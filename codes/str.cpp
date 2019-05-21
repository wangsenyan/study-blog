char *strcpy(char *dst,const char *src)
{
	//assert(dst!=NULL && src!=NULL);
	char *ret=dst;
	while((*dst++=*src++)!='\0');
	return ret;
}

void *memcpy(void *dst,const void *src,size_t size)
{
	char *psrc;
	char *pdst;
	if(NULL==dst||NULL==src)
	   return NULL;
	if((src<dst)&&(char *)src+size>(char *)dst)
	{
		psrc=(char *)src+size-1;
		pdst=(char *)dst+size-1;
		while(size--)
		{
			*pdst--=*psrc--;
		}
	}else{
		psrc=(char *)src;
		pdst=(char *)dst;
		while(size--)
		{
			*pdst++=*psrc++;
		}
	}
	return dst;
}

void *(memset)(void *s,int c,size_t n)
{
	const unsigned char uc=c;
	unsigned char *su;
	for(su=s;0<n;++su,--n)
	  *su=uc;
	return s;
}

void *memmove(void *dest,const void *src,unsigned int const)
{

	assert(dest);
	assert(src);
 
	void *d = dest;
	if (dest < src && (char *)src < (char *)dest + count)
	{
		while (count--)
		{
			//Ë³Ðò
			*(char*)d = *(char*)src;
			d = (char*)d + 1;
			src = (char*)src + 1;
		}
	}
	else
	{
		d = (char*)d + count - 1;
		src = (char*)src + count - 1;
		// ÄæÐò
		while (count--)
		{
			*(char*)d = *(char*)src;
			d = (char*)d - 1;
			src = (char*)src - 1;
		}
	}
	return dest;
}
