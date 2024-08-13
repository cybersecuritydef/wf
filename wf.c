#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

#include "fuzzer.h"


void banner(void){
    printf("################################################\n");
    printf("#              wf (web fuzzer)                 #\n");
    printf("#               Version: 1.0                   #\n");
    printf("#                                              #\n");
    printf("# web fuzzer for security testing and analysis #\n");
    printf("################################################\n\n");
}

void help(void){
    printf("OPTIONS:\n");
    printf("\t-w\t--wordlists=\t: Wordlists files\n");
    printf("\t-v\t--verbose\t: Verbose information\n");
    printf("\t-h\t--help\t\t: Using help\n");
    printf("\t-t\t\t\t: Numbers threads  (default: 20)\n\n\n");

    printf("\t-f\t--follow\t: HTTP redirections\n");
    printf("\t-u\t--url=\t\t: URL for request\n");
    printf("\t-r\t--recursion\t: Recursive path discovery (default: false)\n");
    printf("\t-d\t--post-data=\t: POST data \"username=admin&password=admin\"\n");
    printf("\t-e\t--encode=\t: Encoding payloads (base64, urlencode, durlencode, hex, md5, sha1, sha256, sha512)\n");
    printf("\t-c\t--cookie=\t: Cookie data \"Key1=value1; Key2=value2\"\n");
    printf("\t-H\t--headers=\t: Use header \"Key: Value\". Comma seperated lists headers [,]\n");
    printf("\t-m\t--method=\t: HTTP method request (default: GET)\n");
    printf("\t-b\t\t\t: Show response body (default: false)\n");
    printf("\t-p\t--proxy=\t: Use proxy \"http://example.com:8080\" (Used: http://, socks4://, socks4a://, socks5://, socks5h://)\n");
    printf("\t-V\t--version=\t\t: Version HTTP protocol (default: HTTP/1.1)\n\n\n");

    printf("\t--hsize=\t\t: Hide response size. Comma seperated lists response sizes [,]\n");
    printf("\t--hcode=\t\t: Hide response code. Comma seperated lists response codes [,]\n");
    printf("\t--hword=\t\t: Hide response word. Comma seperated lists words [,]\n");
    printf("\t--ssize=\t\t: Show response size. Comma seperated lists response sizes [,]\n");
    printf("\t--scode=\t\t: Show response code. Comma seperated lists response codes [,]\n");
    printf("\t--sword=\t\t: Show response word. Comma seperated lists words [,]\n");
    printf("EXAMPLES:\n\t");
    printf("wf -u http://example.com/WF -w wordlist.txt\n");
    printf("\twf -u http://example.com/index.php?page=WF --lfi\n");
    printf("\twf -u http://example.com/WF -w wordlist.txt --recursion -c \"isadmin=true; path=/\"\n");
    printf("\twf -u http://example.com/WF -w wordlist.txt  -m PUT\n");
    printf("\twf -u http://example.com/WF -w wordlist.txt  -H \"Accept: */*\"\n");
    printf("\twf -u http://example.com/index.php?id=WF -w wordlist.txt  --encode=base64\n");
    printf("\twf -u http://example.com/login.php -w user.txt -w passwd.txt --hword=\"Login fail\"  -d \"username=WF&password=WF2\"\n");
}


int main(int argc, char **argv){
    int opt = 0;
    int index_opt = 0;
    char shortopts[] = "w:vt:fu:rd:e:c:H:V:p:m:t:bh";
    options opts;
    struct option longopts[] = {
        {"wordlist", 1, NULL, 'w'},
        {"verbose", 0, NULL, 'v'},
        {"help", 0, NULL, 'h'},
        {"follow", 0, NULL, 'f'},
        {"url", 1, NULL, 'u'},
        {"recursion", 0, NULL, 'r'},
        {"post-data", 1, NULL, 'd'},
        {"encode", 1, NULL, 'e'},
        {"method", 1, NULL, 'm'},
        {"cookie", 1, NULL, 'c'},
        {"headers", 1, NULL, 'H'},
        {"version", 1, NULL, 'V'},
        {"proxy", 1, NULL, 'p'},
        {"ssize", 1, NULL, '0'},
        {"scode", 1, NULL, '1'},
        {"sword", 1, NULL, '2'},
        {"hsize", 1, NULL, '3'},
        {"hcode", 1, NULL, '4'},
        {"hword", 1, NULL, '5'},
        {NULL, 0, NULL, 0}
    };
    opterr = false;
    memset(&opts, '\0', sizeof(opts));
    opts.threads = 20;
    while((opt = getopt_long(argc, argv, shortopts, longopts, &index_opt)) != EOF){
        switch(opt){
            case 'w' :
                break;
            case 'v' :
                opts.verbose = true;
                break;
            case 'f':
                opts.follow = true;
                break;
            case 'b' :
                opts.body = true;
                break;
            case 'u' :
                opts.url = optarg;
                break;
            case 'r' :
                opts.recursion = true;
                break;
            case 'd' :
                opts.postdata = optarg;
                break;
            case 'e' :
                opts.encode = optarg;
                break;
            case 'm' :
                opts.method = optarg;
                break;
            case 'c' :
                opts.cookies = optarg;
                break;
            case 'H' :
                opts.headers = optarg;
                break;
            case 't' :
                opts.threads = strtol(optarg, NULL, 10);
                break;
            case 'V' :
                opts.version = optarg;
                break;
            case 'p' :
                opts.proxy = optarg;
                break;
            case '0' : /* ssize */
                opts.ssize = optarg;
                break;
            case '1' : /* scode */
                opts.scode = optarg;
                break;
            case '2' : /* sword */
                opts.sword = optarg;
                break;
            case '3' : /* hsize */
                opts.hsize = optarg;
                break;
            case '4' : /* hcode */
                opts.hcode = optarg;
                break;
            case '5' : /* hword */
                opts.hword = optarg;
                break;
            case 'h' :
                help();
                break;
            default :
                die("[-] Invalid argument!");
        }
    }

    fuzzer(&opts);

    return 0;
}
