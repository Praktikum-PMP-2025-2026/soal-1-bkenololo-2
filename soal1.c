#include <stdio.h>
#include <stdlib.h>

// Definisi Struktur Node untuk Linked List
typedef struct Node {
    int n;
    struct Node* next;
} Node;

// Definisi Struktur Queue
typedef struct {
    Node* front; // Pointer ke elemen paling depan (yang akan dibaca)
    Node* rear;  // Pointer ke elemen paling belakang (tempat data masuk)
} Queue;

// Fungsi inisialisasi antrian kosong
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Mengecek apakah antrian kosong
int isEmpty(Queue* q) {
    return (q->front == NULL);
}

// Mekanisme Menambah Data (Enqueue) - Disisipkan di Rear
void enqueue(Queue* q, int n) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: Memori penuh, tidak dapat menyimpan data.\n");
        return;
    }
    
    // Assign data
    newNode->n = n;
    newNode->next = NULL;
    
    // Jika queue kosong, node baru menjadi front sekaligus rear
    if (isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        // Sambungkan ke belakang, lalu geser rear
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Mengurutkan queue menggunakan Bubble Sort
void bubble_sort(Queue* q, int n) {
    if (q->front == NULL) return; // Handle empty queue

    for (int i = 0; i < n - 1; i++) {
        Node* now = q->front;
        while (now != NULL && now->next != NULL) {
            Node* next = now->next;
            
            // Swap values if current is greater than next
            if (now->n > next->n) {
                int temp = now->n;
                now->n = next->n;
                next->n = temp;
            }
            now = now->next;
        }
    }
}

// Mencetak isi antrian secara berurutan
void printQueue(Queue* q) {
    Node* now = q->front;
    while (now != NULL) {
        printf("%d ", now->n);
        now = now->next;
    }
}

// Menghitung Median dari Linked List yang sudah diurutkan
double getMedian(Queue* q, int count) {
    if (count == 0 || isEmpty(q)) return 0.0;
    
    Node* curr = q->front;
    int mid = count / 2;
    
    // Jika jumlah data ganjil
    if (count % 2 != 0) {
        for (int i = 0; i < mid; i++) {
            curr = curr->next;
        }
        int value = curr->n;
        return value;
    } 
    // Jika jumlah data genap
    else {
        for (int i = 0; i < mid - 1; i++) {
            curr = curr->next;
        }
        double val1 = curr->n;
        curr = curr->next;
        double val2 = curr->n;
        return (val1 + val2) / 2.0;
    }
}

int main() {
    int n;
    int count = 0;
    int status;
    Queue data;
    
    initQueue(&data);
    
    // Membaca input hingga sentinel -1 ditemukan
    while (1) {
        scanf("%d", &n);
        if (n == -1) {
            break; // stop sebelum -1 masuk ke dalam queue
        }
        enqueue(&data, n);
        count++;
    }
    
    // Menampilkan output sesuai format yang diminta
    printf("COUNT %d ", count);
    
    bubble_sort(&data, count);
    
    printf("SORTED ");
    printQueue(&data);
    
    if(count%2 == 0){
        printf("MEDIAN %.2f", getMedian(&data, count));
    }else{
        printf("MEDIAN %.0f", getMedian(&data, count));
    }
    return 0;
}
