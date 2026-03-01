#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Customer
{
    string nama;
    int umur;
    string gender, nomorTelepon, alamat;
    Customer *next;
    Customer *prev;
};
Customer *headCus = NULL;
Customer *tailCus = NULL;

struct Service
{
    string modelMobil, merekMobil, deskripsiKendala, namaMontir, namaCus; // cek udah daftar atau belum
    Service *next;
};
Service *headServ = NULL;
Service *tailServ = NULL;

void tambahCustomer(string nama, int umur, string gender, string nomorTelepon, string alamat)
{
    Customer *baru = new Customer;
    baru->nama = nama;
    baru->umur = umur;
    baru->gender = gender;
    baru->nomorTelepon = nomorTelepon;
    baru->alamat = alamat;
    baru->next = NULL;
    baru->prev = NULL;

    if (headCus == NULL)
    {
        headCus = tailCus = baru;
    }
    else
    {
        tailCus->next = baru;
        baru->prev = tailCus;
        tailCus = baru;
    }
}

void tambahService(string modelMobil, string merekMobil, string deskripsiKendala, string namaMontir, string namaCus)
{
    Service *baru = new Service;
    baru->modelMobil = modelMobil;
    baru->merekMobil = merekMobil;
    baru->deskripsiKendala = deskripsiKendala;
    baru->namaMontir = namaMontir;
    baru->namaCus = namaCus;
    baru->next = NULL;

    if (headServ == NULL)
    {
        headServ = tailServ = baru;
    }
    else
    {
        tailServ->next = baru;
        tailServ = baru;
    }
}

Customer *cekCustomer(string nama)
{
    Customer *temp = headCus;
    while (temp != NULL)
    {
        if (temp->nama == nama)
        {
            return temp;
        }
        else
        {
            temp = temp->next;
        }
    }
    return NULL;
}

void bacaData()
{
    ifstream fileCustomer("Data_Customer.csv"); // baca file
    string nama, umur, gender, nomorTelepon, alamat;
    if (fileCustomer.is_open())
    {
        while (getline(fileCustomer, nama, ';'))
        {
            getline(fileCustomer, umur, ';');
            getline(fileCustomer, gender, ';');
            getline(fileCustomer, nomorTelepon, ';');
            getline(fileCustomer, alamat);
            tambahCustomer(nama, stoi(umur), gender, nomorTelepon, alamat);
        }
        fileCustomer.close();
    }

    ifstream fileService("Data_Service.csv"); // baca file
    string modelMobil, merekMobil, deskripsiKendala, namaMontir, namaCus;
    if (fileService.is_open())
    {
        while (getline(fileService, modelMobil, ';'))
        {
            getline(fileService, merekMobil, ';');
            getline(fileService, deskripsiKendala, ';');
            getline(fileService, namaMontir, ';');
            getline(fileService, namaCus);
            tambahService(modelMobil, merekMobil, deskripsiKendala, namaMontir, namaCus);
        }
        fileService.close();
    }
}

void simpanData()
{
    ofstream fileCustomer("Data_Customer.csv"); // simpan data
    Customer *ambilCustomer = headCus;
    while (ambilCustomer != NULL)
    {
        fileCustomer << ambilCustomer->nama << ";" << ambilCustomer->umur << ";" << ambilCustomer->gender << ";" << ambilCustomer->nomorTelepon << ";" << ambilCustomer->alamat << endl;
        ambilCustomer = ambilCustomer->next;
    }
    fileCustomer.close();

    ofstream fileService("Data_Service.csv"); // simpan data
    Service *ambilService = headServ;
    while (ambilService != NULL)
    {
        fileService << ambilService->modelMobil << ";" << ambilService->merekMobil << ";" << ambilService->deskripsiKendala << ";" << ambilService->namaMontir << ";" << ambilService->namaCus << endl;
        ambilService = ambilService->next;
    }
    fileService.close();
}

void semuaServiceSingkat()
{
    cout << "\n====== All Services ======" << endl;
    Service *srv = headServ;
    while (srv != NULL)
    {
        cout << "-----------------------" << endl;
        cout << "Model Mobil: " << srv->modelMobil << endl;
        cout << "Merek Mobil: " << srv->merekMobil << endl;
        cout << "Kendala: " << srv->deskripsiKendala << endl;
        cout << "Montir: " << srv->namaMontir << endl;
        cout << "Nama Pelanggan: " << srv->namaCus << endl;
        Customer *cstmr = cekCustomer(srv->namaCus);
        if (cstmr)
        {
            cout << "No Telp Pelanggan: " << cstmr->nomorTelepon << endl;
        }
        srv = srv->next;
    }
    cout << "-----------------------" << endl;
    cout << "Press any key to go back ...";
    cin.ignore();
    cin.get();
}

void serviceBaru()
{
    string modelMobil, merekMobil, deskripsiKendala, namaMontir, namaCus;
    cout << "\n====== New Service ======" << endl;
    cin.ignore(1000, '\n');
    cout << "Model Mobil: >";
    cin.ignore();
    getline(cin, modelMobil);
    cout << "Merek Mobil: >";
    getline(cin, merekMobil);
    cout << "Kendala: >";
    getline(cin, deskripsiKendala);
    cout << "Montir: >";
    getline(cin, namaMontir);
    cout << "Nama Pelanggan: >";
    getline(cin, namaCus);

    Customer *cek = cekCustomer(namaCus);
    if (cek == NULL)
    {
        string nomorTelepon, alamat, gender;
        int umur;
        cout << "No Telp Pelanggan: >";
        getline(cin, nomorTelepon);
        cout << "Alamat: >";
        getline(cin, alamat);
        cout << "Umur: >";
        cin >> umur;
        cin.ignore();
        cout << "Gender: >";
        getline(cin, gender);
        tambahCustomer(namaCus, umur, gender, nomorTelepon, alamat);
        cout << "*Pelanggan baru telah terdaftar dan servis berhasil dicatat*" << endl;
    }
    else
    {
        cout << "*Pelanggan sudah terdaftar dan servis berhasil dicatat*" << endl;
    }
    tambahService(modelMobil, merekMobil, deskripsiKendala, namaMontir, namaCus);
    simpanData();
    cout << "Press any key to go back ...";
    cin.get();
}

void riwayatKerjaMontir()
{
    string daftar_nama[] = {"Suby", "Farhan", "Dimas", "Aldo"};
    cout << "\n====== Mechanic's job history ======" << endl;
    for (int i = 0; i < 4; i++)
        cout << i + 1 << ". " << daftar_nama[i] << endl;
    int pilih;
    cout << "Pilihan: ";
    cin >> pilih;

    string target = daftar_nama[pilih - 1];
    cout << "\n====== " << target << "'s Jobs ======" << endl
         << endl;
    Service *srv = headServ;
    while (srv != NULL)
    {
        if (srv->namaMontir == target)
        {
            cout << "-----------------------" << endl;
            cout << "Model Mobil: " << srv->modelMobil << endl;
            cout << "Merek Mobil: " << srv->merekMobil << endl;
            cout << "Kendala: " << srv->deskripsiKendala << endl;
            cout << "Montir: " << srv->namaMontir << endl;
            cout << "Nama Pelanggan: " << srv->namaCus << endl;
            Customer *cstmr = cekCustomer(srv->namaCus);
            if (cstmr)
            {
                cout << "No Telp Pelanggan: " << cstmr->nomorTelepon << endl;
            }
            cout << "-----------------------" << endl
                 << endl;
        }
        srv = srv->next;
    }
    cout << "Press any key to go back ...";
    cin.ignore(1000, '\n');
    cin.get();
}

void semuaDataPelanggan()
{
    cout << "\n====== All Customers ======" << endl
         << endl;
    Customer *cstmr = headCus;
    while (cstmr != NULL)
    {
        cout << "-----------------------" << endl;
        cout << "Nama: " << cstmr->nama << endl;
        cout << "Nomor Telepon: " << cstmr->nomorTelepon << endl;
        cout << "Alamat: " << cstmr->alamat << endl;

        Service *srv = headServ;
        Service *terakhir = NULL;
        while (srv != NULL)
        {
            if (srv->namaCus == cstmr->nama)
                terakhir = srv;
            srv = srv->next;
        }
        if (terakhir)
        {
            cout << "___Servis Terakhir___" << endl;
            cout << "Mobil: " << terakhir->merekMobil << " " << terakhir->modelMobil << endl;
            cout << "Kendala: " << terakhir->deskripsiKendala << endl;
            cout << "Montir: " << terakhir->namaMontir << endl;
        }
        cstmr = cstmr->next;
        cout << "-----------------------" << endl
             << endl;
    }
    cout << "Press any key to go back ...";
    cin.ignore();
    cin.get();
}

void dataPelanggan()
{
    if (headCus == NULL)
        return;
    Customer *cstmr = headCus;
    char scroll;
    do
    {
        cout << "\n====== Customer Data ======" << endl;
        cout << "Nama: " << cstmr->nama << endl;
        cout << "Nomor Telepon: " << cstmr->nomorTelepon << endl;
        cout << "Umur: " << cstmr->umur << endl;
        cout << "Gender: " << cstmr->gender << endl;
        cout << "Alamat: " << cstmr->alamat << endl;

        Service *srv = headServ;
        cout << "\n   3 Servis Terakhir" << endl;
        int hitung = 0;
        while (srv != NULL && hitung < 3)
        {
            if (srv->namaCus == cstmr->nama)
            {
                cout << "-----------------------" << endl;
                cout << "Mobil: " << srv->merekMobil << " " << srv->modelMobil << endl;
                cout << "Kendala: " << srv->deskripsiKendala << endl;
                cout << "Montir: " << srv->namaMontir << endl;
                hitung++;
            }
            srv = srv->next;
        }
        cout << "-----------------------" << endl;
        cout << "[N]ext, [P]revious, [E]xit" << endl;
        cout << "Pilihan: ";
        cin >> scroll;

        if ((scroll == 'N' || scroll == 'n') && cstmr->next != NULL)
            cstmr = cstmr->next;
        else if ((scroll == 'P' || scroll == 'p') && cstmr->prev != NULL)
            cstmr = cstmr->prev;
    } while (scroll != 'E' && scroll != 'e');
}

int main()
{
    bacaData();
    int a, b;

    while (true)
    {
        cout << "\n====== Welcome To Lognuts ======" << endl;
        cout << "Pilih Menu:" << endl;
        cout << "1. Servis" << endl;
        cout << "2. Semua Data Pelanggan" << endl;
        cout << "3. Data Pelanggan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> a;

        if (a == 1)
        {
            cout << "\n====== Services ======" << endl;
            cout << "Pilih menu?" << endl;
            cout << "1. Semua Servis Singkat" << endl;
            cout << "2. Servis Baru" << endl;
            cout << "3. Riwayat Kerja Montir" << endl;
            cout << "Pilihan: ";
            cin >> b;
            if (b == 1)
                semuaServiceSingkat();
            else if (b == 2)
                serviceBaru();
            else if (b == 3)
                riwayatKerjaMontir();
            else
            {
                cout << "Pilihan anda tidak valid!";
            }
        }
        else if (a == 2)
            semuaDataPelanggan();
        else if (a == 3)
            dataPelanggan();
        else if (a == 4)
            break;
        else
        {
            cout << "Pilihan anda tidak valid!";
        }
    }
    return 0;
}