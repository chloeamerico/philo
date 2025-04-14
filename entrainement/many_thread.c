/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:24:58 by camerico          #+#    #+#             */
/*   Updated: 2025/04/11 17:35:34 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// objctif :
// -Créer 5 threads.
// -Chaque thread affiche un message avec son propre numéro.
// -On leur passe cet identifiant en argument.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> 

// Fonction exécutée par chaque thread
void *routine(void *arg)
{
    int id = *(int *)arg; 					// On récupère l'ID passé (on le cast)
    printf("→ Thread %d : Bonjour depuis mon thread !\n", id);
    free(arg);	 							// Libération de l'espace mémoire alloué pour l'ID
    return NULL;
}

int main(void)
{
    const int NB_THREADS = 5;
    pthread_t threads[NB_THREADS];
    int i;

    i = 0;
    while (i < NB_THREADS)
    {
        int *id = malloc(sizeof(int));
        if (!id)
        {
            perror("malloc");
            return (1);
        }
        *id = i + 1;
        if (pthread_create(&threads[i], NULL, routine, id) != 0)
        {
            perror("pthread_create");
            free(id);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < NB_THREADS)
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    printf("Tous les threads ont terminé ✅\n");
    return (0);
}