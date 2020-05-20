#include<stdio.h>
#include"sets.h"

//Functions to implement
Set Union(Set S1,Set S2)
{
    Set S;
    status_code sc;
    InitializeEmptySet(&S);
    int i=0;
    HashElement *ptr=NULL;
    for(i=0;i<S1.HashSize;i++)
    {
        ptr=(S1.HashTablePtr)[i];
        while(ptr!=NULL)
        {
            if(ptr!=NULL)
            {
                sc=add(&S,ptr->set_element);
            }
            ptr=ptr->next;
        }
    }
    for(i=0;i<S2.HashSize;i++)
    {
        ptr=(S2.HashTablePtr)[i];
        while(ptr!=NULL)
        {
            if(ptr!=NULL)
            {
                if(isElementOf(ptr->set_element,S)==FALSE)
                {
                    sc=add(&S,ptr->set_element);
                }
            }
            ptr=ptr->next;
        }
    }
    return S;
}

Set Intersection(Set S1,Set S2)
{
    Set S;
    InitializeEmptySet(&S);
    int i=0;
    HashElement *ptr=NULL;
    status_code sc;
    if(Size(S1)<Size(S2))
    {
        for(i=0;i<S1.HashSize;i++)
        {
            ptr=(S1.HashTablePtr)[i];
            while(ptr!=NULL)
            {
                if(ptr!=NULL)
                {
                    if(isElementOf(ptr->set_element,S2)==TRUE)
                    {
                        sc=add(&S,ptr->set_element);
                    }
                }
                ptr=ptr->next;
            }
        }
    }
    else
    {
        S=Intersection(S2,S1);
    }
    return S;
}

Set Difference(Set S1,Set S2)//S1-S2
{
    Set S;
    status_code sc;
    InitializeEmptySet(&S);
    int i=0;
    HashElement *ptr=NULL;
    for(i=0;i<S1.HashSize;i++)
    {
        ptr=(S1.HashTablePtr)[i];
        while(ptr!=NULL)
        {
            if(ptr!=NULL)
            {
                if(isElementOf(ptr->set_element,S2)==FALSE)
                {
                    sc=add(&S,ptr->set_element);
                }
            }
            ptr=ptr->next;
        }
    }
    return S;
}

Bool Subset(Set S1,Set S2)//Checks for S1 as subset of S2
{
    Bool retval=TRUE;
    int i=0;
    HashElement *ptr=NULL;
    for(i=0;i<S1.HashSize && retval==TRUE;i++)
    {
        ptr=(S1.HashTablePtr)[i];
        while(ptr!=NULL)
        {
            if(ptr!=NULL)
            {
                if(isElementOf(ptr->set_element,S2)==FALSE)
                {
                    retval=FALSE;
                }
            }
            ptr=ptr->next;
        }
    }
    return retval;
}

void main()
{
    Set S;
    InitializeEmptySet(&S);
    char str[10];
    char **list=NULL;
    int size=0;
    status_code sc;
    
    //-------------BELOW part is a tester to test add,delete from set------
    /*
    int loop=0,choice=0;
    while(loop==0)
    {
        printf("\n");
        printf("\nWhat do you want to do:");
        printf("\n1.Enter element in set");
        printf("\n2.Delete element from set");
        printf("\n3.Print the set");
        printf("\n4.Enumerate current set to string array");
        printf("\nYour Choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                    printf("\nEnter the element(alphabetic string):");
                    scanf("%s",str);
                    sc=add(&S,str);
                    printf("HashIndex:%d",HashFunction(str,S.HashSize));
                    if(sc==SUCCESS)
                    {
                        printf("\nSuccessful Insertion");
                    }
                    else
                    {
                        printf("\nSome error occured!!");
                    }
                    break;

            case 2:
                    printf("\nEnter the element to be deleted:");
                    scanf("%s",str);
                    sc=delete(&S,str);
                    if(sc==SUCCESS)
                    {
                        printf("\nSuccessful Deletion");
                    }
                    else
                    {
                        printf("\nElement is not present in the set!!");
                    }
                    break;

            case 3:
                    printSet(S);
                    break;

            case 4:
                    //free earlier list space before alloting new one....
                    flushStringArray(list,&size);
                    list=Enumerate(S,&size);
                    printStringArray(list,size);
                    break;

            default:
                    loop=1;
                    break;
        }
    }
    */
    //-----END of tester for add,remove part-------------------------------
}