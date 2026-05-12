#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<errno.h>
#include<stdbool.h>

#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sys/random.h>

#define salt_size 32
#define hash_size 32

bool generate_salt(unsigned char* salt){
    
    ssize_t result = getrandom(salt, salt_size, 0);

    if (result < 0) {
        if (errno == EAGAIN) {
            printf("Entropy pool not ready; try again later.\n");
        } else {
            perror("getrandom error");
        }
        return false;
    }

    return true;
}

bool store_password(const char* password){
    unsigned char hash[hash_size];
    unsigned char salt[salt_size];

    if(!(generate_salt(salt))){
        return false;
    }
    FILE* fp;

    PKCS5_PBKDF2_HMAC(
    password,      // password
    strlen(password),

    salt,              // salt
    salt_size,

    100000,            // iterations

    EVP_sha256(),      // hash algorithm

    hash_size,                // output length

    hash               // output buffer
    );

    fp = fopen("./auth.txt","wb");
    if(fp == NULL){
        return false;
    }
    fwrite(salt,1,salt_size,fp);
    fwrite(hash,1,hash_size,fp);
    fclose(fp);

    
    return true;

}

bool verify_password(const char* entered_password){//const char for cpp compatibility and also to protect original value of string
    unsigned char salt[salt_size];
    unsigned char hash[hash_size];
    unsigned char new_hash[hash_size];
    FILE* fp;

    fp = fopen("./auth.txt","rb");
    if(fp==NULL){
        printf("auth.txt missing\n");
        return false;
    }

    fread(salt , 1, salt_size, fp);
    fread(hash,1,hash_size,fp);
    fclose(fp);

    PKCS5_PBKDF2_HMAC(
    entered_password,      // password
    strlen(entered_password),

    salt,              // salt
    salt_size,

    100000,            // iterations

    EVP_sha256(),      // hash algorithm

    hash_size,                // output length

    new_hash               // output buffer
    );

    return memcmp(hash,new_hash,hash_size) == 0;//memcmp return zero if the string match
}

