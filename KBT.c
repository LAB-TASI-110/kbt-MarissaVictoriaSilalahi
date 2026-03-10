#include <stdio.h>
#include <stdlib.h> // Untuk system("cls") atau system("clear")
#include <string.h> // Untuk strcmp

#define MAX_ROUTES 5
#define MAX_TICKETS 10
#define MAX_STR 50

// Struktur untuk rute
struct Route {
    int id;
    char origin[MAX_STR];
    char destination[MAX_STR];
    int price;
    int available_seats;
};

// Struktur untuk tiket yang dipesan
struct Ticket {
    int ticket_id;
    int route_id;
    char passenger_name[MAX_STR];
    int quantity;
    int total_price;
};

int main() {
    // Data rute yang tersedia
    struct Route routes[MAX_ROUTES] = {
        {1, "Medan", "Siantar", 50000, 10},
        {2, "Medan", "Balige", 75000, 8},
        {3, "Medan", "Tarutung", 100000, 12},
        {4, "Siantar", "Balige", 40000, 15},
        {5, "Balige", "Tarutung", 30000, 7}
    };

    // Array untuk menyimpan tiket yang dipesan
    struct Ticket booked_tickets[MAX_TICKETS];
    int num_booked_tickets = 0;
    int next_ticket_id = 1001; // ID awal untuk tiket

    int choice;

    do {
        // Membersihkan layar konsol (untuk Windows, gunakan "cls", untuk Linux/macOS gunakan "clear")
        system("cls"); // Ubah ke system("clear") jika di Linux/macOS
        printf("==========================================\n");
        printf(" SISTEM TICKETING KOPERASI BINTANG TAPANULI\n");
        printf("==========================================\n");
        printf("1. Lihat Daftar Rute\n");
        printf("2. Pesan Tiket\n");
        printf("3. Tampilkan Tiket yang Sudah Dipesan\n");
        printf("4. Keluar\n");
        printf("==========================================\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Menampilkan daftar rute
                printf("\n=========================\n");
                printf(" DAFTAR RUTE KBT\n");
                printf("=========================\n");
                printf("ID | Asal        | Tujuan      | Harga     | Kursi Tersedia\n");
                printf("----------------------------------------------------------------\n");
                for (int i = 0; i < MAX_ROUTES; i++) {
                    printf("%-2d | %-11s | %-11s | Rp %-7d | %-15d\n",
                           routes[i].id, routes[i].origin, routes[i].destination,
                           routes[i].price, routes[i].available_seats);
                }
                printf("----------------------------------------------------------------\n");
                printf("\nTekan ENTER untuk kembali ke menu utama...");
                fflush(stdin); // Membersihkan buffer input
                getchar();     // Menunggu input ENTER
                break;
            }
            case 2: {
                // Memesan tiket
                if (num_booked_tickets >= MAX_TICKETS) {
                    printf("\nMaaf, kuota pemesanan tiket sudah penuh.\n");
                    printf("\nTekan ENTER untuk kembali ke menu utama...");
                    fflush(stdin);
                    getchar();
                    break;
                }

                int route_id_to_book;
                int quantity_to_book;
                char passenger_name[MAX_STR];
                int found_route = 0;
                int route_index = -1;

                printf("\n=========================\n");
                printf(" PESAN TIKET\n");
                printf("=========================\n");
                printf("Masukkan ID Rute yang ingin dipesan: ");
                scanf("%d", &route_id_to_book);

                for (int i = 0; i < MAX_ROUTES; i++) {
                    if (routes[i].id == route_id_to_book) {
                        found_route = 1;
                        route_index = i;
                        break;
                    }
                }

                if (!found_route) {
                    printf("ID Rute tidak ditemukan.\n");
                } else {
                    printf("Jumlah tiket yang ingin dipesan: ");
                    scanf("%d", &quantity_to_book);

                    if (quantity_to_book <= 0) {
                        printf("Jumlah tiket harus lebih dari 0.\n");
                    } else if (quantity_to_book > routes[route_index].available_seats) {
                        printf("Maaf, kursi tersedia hanya %d.\n", routes[route_index].available_seats);
                    } else {
                        printf("Masukkan Nama Penumpang: ");
                        fflush(stdin); // Membersihkan buffer sebelum membaca string
                        fgets(passenger_name, MAX_STR, stdin);
                        passenger_name[strcspn(passenger_name, "\n")] = 0; // Menghapus newline character

                        // Simpan tiket
                        booked_tickets[num_booked_tickets].ticket_id = next_ticket_id++;
                        booked_tickets[num_booked_tickets].route_id = route_id_to_book;
                        strcpy(booked_tickets[num_booked_tickets].passenger_name, passenger_name);
                        booked_tickets[num_booked_tickets].quantity = quantity_to_book;
                        booked_tickets[num_booked_tickets].total_price = quantity_to_book * routes[route_index].price;

                        routes[route_index].available_seats -= quantity_to_book; // Kurangi kursi tersedia
                        num_booked_tickets++;

                        printf("\nSelamat! Tiket berhasil dipesan.\n");
                        printf("Detail Tiket:\n");
                        printf("  ID Tiket: %d\n", booked_tickets[num_booked_tickets-1].ticket_id);
                        printf("  Rute: %s -> %s\n", routes[route_index].origin, routes[route_index].destination);
                        printf("  Penumpang: %s\n", booked_tickets[num_booked_tickets-1].passenger_name);
                        printf("  Jumlah: %d\n", booked_tickets[num_booked_tickets-1].quantity);
                        printf("  Total Harga: Rp %d\n", booked_tickets[num_booked_tickets-1].total_price);
                    }
                }
                printf("\nTekan ENTER untuk kembali ke menu utama...");
                fflush(stdin);
                getchar();
                break;
            }
            case 3: {
                // Menampilkan tiket yang sudah dipesan
                printf("\n==========================================\n");
                printf(" TIKET YANG SUDAH DIPESAN\n");
                printf("==========================================\n");
                if (num_booked_tickets == 0) {
                    printf("Belum ada tiket yang dipesan.\n");
                } else {
                    printf("ID Tiket | Rute             | Penumpang          | Jumlah | Total Harga\n");
                    printf("--------------------------------------------------------------------------------\n");
                    for (int i = 0; i < num_booked_tickets; i++) {
                        char route_info[MAX_STR * 2];
                        int current_route_index = -1;
                        for(int j=0; j<MAX_ROUTES; j++) {
                            if(routes[j].id == booked_tickets[i].route_id) {
                                current_route_index = j;
                                break;
                            }
                        }
                        if (current_route_index != -1) {
                            sprintf(route_info, "%s -> %s", routes[current_route_index].origin, routes[current_route_index].destination);
                        } else {
                            strcpy(route_info, "Tidak Diketahui");
                        }
                        printf("%-9d| %-16s | %-18s | %-6d | Rp %d\n",
                               booked_tickets[i].ticket_id,
                               route_info,
                               booked_tickets[i].passenger_name,
                               booked_tickets[i].quantity,
                               booked_tickets[i].total_price);
                    }
                    printf("--------------------------------------------------------------------------------\n");
                }
                printf("\nTekan ENTER untuk kembali ke menu utama...");
                fflush(stdin);
                getchar();
                break;
            }
            case 4: {
                // Keluar dari program
                printf("\nTerima kasih telah menggunakan Sistem Ticketing KBT. Sampai jumpa!\n");
                break;
            }
            default: {
                printf("\nPilihan tidak valid. Silakan masukkan angka 1-4.\n");
                printf("\nTekan ENTER untuk kembali ke menu utama...");
                fflush(stdin);
                getchar();
                break;
            }
        }
    } while (choice != 4);

    return 0;
}
