#include<stdio.h>
#include"sets.h"

#define MAX_SCAN 20
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
    if(Size(S1)<=Size(S2))
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

void EditSetUI(Set *S)//Available for dynamic sets only...
{
    int exit=0;
    int choice=0;
    char str[MAX_SCAN];
    status_code sc;
    while(exit==0)
    {
        printf("\n");
        printf("\nWhat do you want to do:");
        printf("\n1.Enter element in set");
        printf("\n2.Delete element from set");
        printf("\n3.Print the set");
        printf("\n4.Any other number to go back");
        printf("\nYour Choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                    printf("\nEnter the element(alphabetic string):");
                    scanf("%s",str);
                    sc=add(S,str);
                    printf("HashIndex:%d",HashFunction(str,S->HashSize));
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
                    sc=delete(S,str);
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
                    printSet(*S);
                    break;

            default:
                    exit=1;
                    break;
        }
    }
    
}

void FlushSet(Set *S)
{
    HashElement *ptr=NULL,*prev=NULL;
    int i=0;
    for(i=0;i<S->HashSize;i++)
    {
        ptr=(S->HashTablePtr)[i];
        while(ptr!=NULL)
        {
            prev=ptr;
            ptr=ptr->next;
            free(prev->set_element);
            free(prev);
        }
    }
    free(S->HashTablePtr);
    S->cardinality=0;
    S->HashTablePtr=NULL;
}

void main()
{
    Set S,S1,S2;
    InitializeEmptySet(&S);
    InitializeEmptySet(&S1);
    InitializeEmptySet(&S2);
    int exit=0;
    int choice;
    int isStatic=0;
    Bool isSubset;
    
    printf("\n");
    printf("\nWhat kind of allocation do you wamt:");
    printf("\n1.Dynamic");
    printf("\n2.Static");
    printf("\nYour Choice:");
    scanf("%d",&isStatic);

    switch(isStatic)
    {
        case 1: 
                while(exit==0)
                {
                    printf("\n");
                    printf("\nWhat do you want to do:");
                    printf("\n1.Edit Set 'S1'");
                    printf("\n2.Edit Set 'S2'");
                    printf("\n3.Print Both Sets");
                    printf("\n4.Get the Union of the sets in Set 'S'");
                    printf("\n5.Get the Intersection of the sets in Set 'S'");
                    printf("\n6.Get the Difference of the sets in Set 'S'");
                    printf("\n7.Check whether S1 is a subset of S2");
                    printf("\n8.Any other number to end program");
                    printf("\nYour Choice:");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                        case 1:
                                EditSetUI(&S1);
                                break;
                        
                        case 2:
                                EditSetUI(&S2);
                                break;

                        case 3:
                                printf("\n");
                                printf("\nSet S1:");
                                printSet(S1);
                                printf("\n");
                                printf("\nSet S2:");
                                printSet(S2);
                                break;

                        case 4:
                                S=Union(S1,S2);
                                printSet(S);
                                FlushSet(&S);
                                //Remember to free all stuff in S
                                break;

                        case 5:
                                S=Intersection(S1,S2);
                                printSet(S);
                                FlushSet(&S);
                                //Remember to free all stuff in S
                                break;

                        case 6:
                                S=Difference(S1,S2);
                                printSet(S);
                                FlushSet(&S);
                                //Remember to free all stuff in S
                                break;

                        case 7:
                                isSubset=Subset(S1,S2);
                                if(isSubset==TRUE)
                                {
                                    printf("\n\nYes,it is a subset");
                                }
                                else
                                {
                                    printf("\n\nNo,it isin't a subset");
                                }
                                break;

                        default:
                                exit=1;
                                printf("\n\nFreeing Up Memory....");
                                FlushSet(&S1);
                                FlushSet(&S2);
                                printf("\nDone!!\n");
                                break;

                    }
                }
                break;

        case 2:
                //char **list={"dhruv","good"};//Need a static 2d char array...
                ;
                char list1[][MAX_SCAN]={"dhruv","good"};
                char list2[][MAX_SCAN]={"good","neat","happy"};
                int size1=2,size2=3;
                Build(list1,size1,&S1);
                Build(list2,size2,&S2);
                printf("Set S1:");
                printSet(S1);
                printf("Set S2:");
                printSet(S2);
                S=Union(S1,S2);
                printf("\nThe union is:");
                printSet(S);
                FlushSet(&S);
                S=Intersection(S1,S2);
                printf("\nThe intersection is:");
                printSet(S);
                FlushSet(&S);
                S=Difference(S1,S2);
                printf("\nThe difference(S1-S2) is:");
                printSet(S);
                FlushSet(&S);
                isSubset=Subset(S1,S2);
                if(isSubset==TRUE)
                {
                    printf("\nYes,S1 is a subset of S2");
                }
                else
                {
                    printf("\nNo,S1 is not a subset of S2");
                }
                FlushSet(&S1);
                FlushSet(&S2);
                break;
    
        default:
                break;

    }
        
    
}
    






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
