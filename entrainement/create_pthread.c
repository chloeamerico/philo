/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:15:47 by camerico          #+#    #+#             */
/*   Updated: 2025/04/10 19:17:04 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>  // pour les fonctions de threads
#include <stdio.h>    // pour printf

// Cette fonction sera exécutée par le thread
void *hello(void *arg)
{
    printf("Salut depuis un thread !\n");
    return NULL;
}

int main()
{
    pthread_t thread; // on déclare une variable de type "pthread_t" : c’est notre thread

    // On crée le thread et on lui dit d'exécuter la fonction "hello"
    pthread_create(&thread, NULL, hello, NULL);

    // On attend que le thread ait terminé avant de quitter le programme
    pthread_join(thread, NULL);

    return 0;
}

//proto :
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);