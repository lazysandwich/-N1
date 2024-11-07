#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MAIL 100
#define MAX_ADDRESS_LEN 100
#define MAX_POSTAL_ID_LEN 15
#define MAX_INDEX_LEN 7

typedef struct {
    char city[MAX_ADDRESS_LEN];
    char street[MAX_ADDRESS_LEN];
    unsigned int house_number;
    char building[MAX_ADDRESS_LEN];
    unsigned int apartment_number;
    char index[MAX_INDEX_LEN];
} Address;

typedef struct {
    Address recipient_address;
    double parcel_weight; 
    char postal_identifier[MAX_POSTAL_ID_LEN];
    char creation_time[20];
    char delivery_time[20];
} Mail;

typedef struct {
    Address post_office_address;
    Mail* mail_array;
    size_t mail_count;
} Post;

void initialize_post(Post* post, Address address) {
    post->post_office_address = address;
    post->mail_array = malloc(MAX_MAIL * sizeof(Mail));
    post->mail_count = 0;
}

void add_mail(Post* post, Mail mail) {
    if (post->mail_count < MAX_MAIL) {
        post->mail_array[post->mail_count++] = mail;
        sort_mail(post);
    }
    else {
        printf("массив письм загружен.\n");
    }
}

void remove_mail(Post* post, const char* identifier) {
    for (size_t i = 0; i < post->mail_count; i++) {
        if (strcmp(post->mail_array[i].postal_identifier, identifier) == 0) {
            for (size_t j = i; j < post->mail_count - 1; j++) {
                post->mail_array[j] = post->mail_array[j + 1];
            }
            post->mail_count--;
            printf("Mail удален.\n");
            return;
        }
    }
    printf("Mail не найден.\n");
}

int compare_mail(const void* a, const void* b) {
    const Mail* mailA = (const Mail*)a;
    const Mail* mailB = (const Mail*)b;
    int index_cmp = strcmp(mailA->recipient_address.index, mailB->recipient_address.index);
    if (index_cmp == 0) {
        return strcmp(mailA->postal_identifier, mailB->postal_identifier);
    }
    return index_cmp;
}

void sort_mail(Post* post) {
    qsort(post->mail_array, post->mail_count, sizeof(Mail), compare_mail);
}

void print_mail(const Mail* mail) {
    printf("ID почты: %s\n", mail->postal_identifier);
    printf("ID получателя: %s\n", mail->recipient_address.index);
    printf("дата заказа: %s\n", mail->creation_time);
    printf("дата доставки: %s\n", mail->delivery_time);
    printf("вес: %.2f\n", mail->parcel_weight);
    printf("------------------------\n");
}

void search_mail_by_identifier(Post* post, const char* identifier) {
    for (size_t i = 0; i < post->mail_count; i++) {
        if (strcmp(post->mail_array[i].postal_identifier, identifier) == 0) {
            print_mail(&post->mail_array[i]);
            return;
        }
    }
    printf("Mail не найден.\n");
}

void print_delivered_items(Post* post) {
    time_t now = time(NULL);
    struct tm* current_time = localtime(&now);
    for (size_t i = 0; i < post->mail_count; i++) {
        struct tm delivery_tm;
        strptime(post->mail_array[i].delivery_time, "%d:%m:%Y %H:%M:%S", &delivery_tm);
        if (difftime(mktime(&delivery_tm), now) <= 0) {
            print_mail(&post->mail_array[i]);
        }
    }
}

void print_expired_items(Post* post) {
    time_t now = time(NULL);
    for (size_t i = 0; i < post->mail_count; i++) {
        struct tm delivery_tm;
        strptime(post->mail_array[i].delivery_time, "%d:%m:%Y %H:%M:%S", &delivery_tm);
        if (difftime(now, mktime(&delivery_tm)) > 0) {
            print_mail(&post->mail_array[i]);
        }
    }
}

void free_post(Post* post) {
    free(post->mail_array);
}

void interactive_menu(Post* post) {
    char command[20];
    while (1) {
        printf("введите комманду (add, remove, search, delivered, expired, exit): ");
        scanf("%s", command);
        if (strcmp(command, "add") == 0) {
            Mail mail;
            printf("введите обазначение посылки: ");
            scanf("%s", mail.postal_identifier);
            printf("введите ID получателя: ");
            scanf("%s", mail.recipient_address.index);
            printf("введите дату заказа (дд:ММ:гггг чч:мм:сс): ");
            scanf("%s", mail.creation_time);
            printf("введите дату доставки (дд:MM:гггг чч:мм:сс): ");
            scanf("%s", mail.delivery_time);
            printf("введите вес посылки: ");
            scanf("%lf", &mail.parcel_weight);
            add_mail(post, mail);
        } 
        else if (strcmp(command, "remove") == 0) {
            char identifier[MAX_POSTAL_ID_LEN];
            printf("введите id посылки: ");
            scanf("%s", identifier);
            remove_mail(post, identifier);
        } 
        else if (strcmp(command, "search") == 0) {
            char identifier[MAX_POSTAL_ID_LEN];
            printf("введите id посылки: ");
            scanf("%s", identifier);
            search_mail_by_identifier(post, identifier);
        }
        else if (strcmp(command, "delivered") == 0) {
            print_delivered_items(post);
        }
        else if (strcmp(command, "expired") == 0) {
            print_expired_items(post);
        }
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            printf("нет такой команды.\n");
        }
    }
}

int main() {
    Post post;
    Address post_office_address = {"город", "улица", 123, "строение_а", 1, "123456"};
    initialize_post(&post, post_office_address);
    interactive_menu(&post);
    free_post(&post);
    return 0;
}