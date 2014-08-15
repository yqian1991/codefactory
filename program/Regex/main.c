#include <stdio.h>
#include <stdlib.h>

int match(char *regexp, char *text);
int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);

int main()
{
    int i = 0;
    i=match("x*y^ngt$","xeryngt");
    printf("%d\n",i);
    return 0;
}

/*search for regexp anywhere in text*/
int match(char *regexp, char *text)
{
    if (regexp[0]=='^')//固定位置的匹配，字符必须对应匹配

        return matchhere(regexp+1, text);
    do
    {
        if(matchhere(regexp, text))
        {//不是^时，就从第一个开始匹配，直到结束
            return 1;
        }

    }while(*text++!='\0');

    return 0;
}

/*matchhere:search for regexp at beginning of text*/
int matchhere(char *regexp, char *text)
{//正则表达式的字符与文本的第一个字符匹配
    if(regexp[0] == '\0')
        return 1;

    if(regexp[1] == '*')//如果字符后面有一个*号，那就从text中找出一个与*后字符匹配的都算成功
                        //例如x*y,与xadfdfgfhadsfsdy匹配
        return matchstar(regexp[0], regexp+2,text);

    if(regexp[0] == '$' && regexp[1]=='\0')
        return *text == '\0';

    if(*text!='\0' && (regexp[0]=='.' ||regexp[0]==*text) )
        return matchhere(regexp+1,text+1);

    return 0;
}

/*matchstar:search for c*regexp at beginning of text*/
int matchstar(int c, char *regexp, char *text)
{
    do
    {/* a*matches zero or more instances*/
        if(matchhere(regexp, text))
            return 1;

    }while(*text !='\0' && (*text++==c || c=='.'));

    return 0;
}
