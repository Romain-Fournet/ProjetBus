#include <stdio.h>
#include <stddef.h>

#include "sort.h"
#include "types.h"
#include "listeDouble.h"

int tailleListe(TlisteStation listeStation)
{
    int i = 0;
    while (listeStation != NULL)
    {
        i++;
        listeStation = listeStation->suiv;
    }
    return i;
}

void sortCoutMaintenance(Tstation *tab[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (getCoutMaintenance(tab[j]) < getCoutMaintenance(tab[j + 1]))
            {
                Tstation *temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
    printf("Stations triees par cout de maintenance decroissant :\n");
    for (int i = 0; i < len; i++)
    {
        printf("Station %d (%s) : Cout de maintenance = %d\n", getIdStation(tab[i]), getNomStation(tab[i])[0] == '\0' ? "TRONCON" : getNomStation(tab[i]), getCoutMaintenance(tab[i]));
    }
}

int compareDates(TDate date1, TDate date2)
{
    if (date1.annee != date2.annee)
    {
        return date1.annee - date2.annee;
    }
    if (date1.mois != date2.mois)
    {
        return date1.mois - date2.mois;
    }
    return date1.jour - date2.jour;
}

void sortDateDerniereMaintenance(Tstation *tab[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (compareDates(getDateDerniereMaintenance(tab[j]), getDateDerniereMaintenance(tab[j + 1])) > 0)
            {
                Tstation *temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
    printf("Stations triees par date de maintenance de facon croissante :\n");
    for (int i = 0; i < len; i++)
    {
        TDate date = getDateDerniereMaintenance(tab[i]);
        printf("Station %d (%s): Date de maintenance = %02d/%02d/%04d\n",
               getIdStation(tab[i]),
               getNomStation(tab[i])[0] == '\0' ? "TRONCON" : getNomStation(tab[i]),
               date.jour,
               date.mois,
               date.annee);
    }
};

void sort(TlisteStation myLigne)
{
    int len = tailleListe(myLigne);
    Tstation *tab[len];
    for (int i = 0; i < len; i++)
    {
        tab[i] = getPtrData(myLigne);
        myLigne = getNextCell(myLigne);
    }
    // Tris à bulles:
    // Tri par coût de maintenance (décroissant)
    sortCoutMaintenance(tab, len);
    // Tri par date de maintenance (croissant)
    sortDateDerniereMaintenance(tab, len);
}