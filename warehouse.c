#include "slots.h"
#include <stdio.h>
#include <stdlib.h>

struct Q
{
  int bin_number;
  struct Q* next;
};
int q_size;
struct Q* getQNode(int n)
{
    struct Q* newNode = (void*)malloc(sizeof(struct Q));
    newNode->bin_number=n;
    newNode->next=0;
    return newNode;
}

struct Q* head;

void enqueue(int n)
{
    
    if(head==0)
    {printf("\n enqueuing %d",n);
        head=getQNode(n);
    }
    else
    {printf("\n enqueuing %d",n);
        struct Q* newNode=getQNode(n);
        newNode->next=head;
        head=newNode;
    }
}

int dequeue()
{
	int result = -1;
    if(head!=0)
    {   q_size--;
        if(head->next==0)
        {
            head=0;
        }
        else
        {
        struct Q* tmp = head;
        while(tmp->next->next!=0)
        {
            tmp=tmp->next;
        }
		result=tmp->next->bin_number;
        tmp->next=0;
        }
    }
	return result;
}

int check_table(int bNum)   // returns -1 if bin not found else enqueues the found bin and return the found bin number.
{
    int result = -1;
    if(head!=0)
    {
         struct Q* tmp = head;
         while(tmp->bin_number!=bNum && tmp->next!=0)
         {
             tmp=tmp->next;
         }
         
         if(tmp->bin_number==bNum)
         {
             struct Q* newTmp = head;
             printf("\n head is : %d tmp is: %d",head->bin_number,tmp->bin_number);
             if(newTmp!=tmp)
             {
	     printf("\nhead is not equal to tmp");
                while(newTmp->next!=tmp)
                {
                    newTmp=newTmp->next;
                }
                result =newTmp->next->bin_number;
                enqueue(result);
                newTmp->next=newTmp->next->next;
             }
         }
    }
    return result;
}

void print()
{
 printf("\n Q Size : %d Printing Queue : ",q_size);
  if(head!=0)
 {
     struct Q* tmp = head;
     while(tmp->next!=0)
     {
         printf("\t %d",tmp->bin_number);
         tmp=tmp->next;
     }
       printf("\t %d \n",tmp->bin_number);
}
}



int main(int argc, char ** argv) {
	head=0;
	int bin,free_bin,free_slot;
	free_slot=-1;
	q_size=0;
	initSlots();
	while(1==scanf("%d",&bin)) {
		free_bin=0;

	
		if (-1==findSlot(bin)) {
			
			if(q_size==4)
			{
			free_bin = dequeue();
			free_slot=findSlot(free_bin);
			}
			else
			{
			if(free_slot==3)
			free_slot=0;
			else
			free_slot++;
			}
			getBin(bin,free_slot);
			enqueue(bin);
	                q_size++;
			print();
		}
		else
		{
		 check_table(bin);
		}
		getWidget(bin);
	}
	printEarnings();
	return 0;
}

