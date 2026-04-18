#include <bits/stdc++.h>
using namespace std;

struct Product
{
    int id;
    char name[30];
    float price;
    int qty;
    Product* next;
};

Product* head=NULL;



Product* create(int id, const char* name, float price, int qty)
{
    Product* p=(Product*) malloc(sizeof(Product));
    p->id=id;
    strcpy(p->name, name);
    p->price=price;
    p->qty=qty;
    p->next=NULL;
    return p;
}

void addProduct(int id, const char* name, float price, int qty)
{
    Product* p=create(id, name, price, qty);

    if(head==NULL)
    {
        head=p;
    }
    else
    {
        Product* temp=head;
        while(temp->next !=NULL)
            temp=temp->next;
        temp->next=p;
    }
    cout<<"Added!\n";
}

void showProducts()
{
    Product* temp=head;
    if(!temp)
    {
        cout<<"No products\n";
        return;
    }

    while(temp)
    {
        cout<<"ID: "<<temp->id<<", Name: "<<temp->name
            <<", Price: "<<temp->price
            <<", Qty: "<<temp->qty<<endl;
        temp=temp->next;
    }
}

void searchProduct(int id)
{
    Product* temp=head;
    while(temp)
    {
        if(temp->id==id)
        {
            cout<<"Found: "<<temp->name<<" Price: "<<temp->price<<endl;
            return;
        }
        temp=temp->next;
    }
    cout<<"Not found\n";
}

void deleteProduct(int id)
{
    Product *temp=head, *prev=NULL;

    while(temp)
    {
        if (temp->id==id)
        {
            if (prev==NULL)
            {
                head=temp->next;
            }
            else
            {
                prev->next=temp->next;
            }
            free(temp);
            cout<<"Deleted\n";
            return;
        }
        prev=temp;
        temp=temp->next;
    }
    cout<<"Not found\n";
}

int main()
{
    int choice, id, qty;
    float price;
    char name[30];

    while(1)
    {
        cout<<"               Welcome To BUBT General Store\n1.Add\n2.Show\n3.Search\n4.Delete\n5.Exit\n";
        cin>>choice;

        switch(choice)
        {
        case 1:
            cout<<"Enter id name price qty: ";
            cin>>id>>name>>price>>qty;
            addProduct(id, name, price, qty);
            break;

        case 2:
            showProducts();
            break;

        case 3:
            cout<<"Enter id: ";
            cin>>id;
            searchProduct(id);
            break;

        case 4:
            cout<<"Enter id: ";
            cin>>id;
            deleteProduct(id);
            break;

        case 5:
            exit(0);
        }
    }
}
