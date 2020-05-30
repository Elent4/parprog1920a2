// ... ο κώδικάς σας για την υλοποίηση του quicksort
// με pthreads και thread pool...

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define CUTOFF 100
#define M 10000
#define QUEUE_SIZE M


// conditional variable, signals a put operation (receiver waits on this)
pthread_cond_t msg_in = PTHREAD_COND_INITIALIZER;
// conditional variable, signals a get operation (sender waits on this)
pthread_cond_t msg_out = PTHREAD_COND_INITIALIZER;
// mutex protecting common resources
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void inssort(double *array, int n) {
    int i, j;
    double t;
    for (i = 1; i < n; i++) {
        j = i;
        while ((j > 0) && (array[j - 1] > array[j])) {
            t = array[j - 1];  array[j - 1] = array[j];
            array[j] = t;
            j--;
        }
    }
}



// The algorithm to partition the array
int partition(double *array, int n) {
    int first, last, middle;
    double t, p;
    int i, j;

    // take first, last and middle positions
    first = 0;
    middle = n / 2;
    last = n - 1;

    // put median-of-3 in the middle
    if (array[middle] < array[first]) {
        t = array[middle];
        array[middle] = array[first];
        array[first] = t;
    }
    if (array[last] < array[middle]) {
        t = array[last];
        array[last] = array[middle];
        array[middle] = t;
    }
    if (array[middle] < array[first]) {
        t = array[middle];
        array[middle] = array[first];
        array[first] = t;
    }

    // partition (first and last are already in correct half)
    p = array[middle]; // pivot
    for (i = 1, j = n - 2;; i++, j--) {
        while (array[i] < p) {
            i++;
        }
        while (p < array[j]) {
            j--;
        }
        if (i >= j) {
            break;
        }

        t = array[i];
        array[i] = array[j];
        array[j] = t;
    }
    // return position of pivot
    return i;
}

int main() {
  	double *array;
  	int i;

	array = (double *)malloc(M*sizeof(double));
	if (array == NULL) {
		printf("error in malloc\n");
		exit(1);
	}

  	// fill array with random numbers
  	srand(time(NULL));
	for (i = 0; i < M; i++) {
    		array[i] = (double)rand() / RAND_MAX;
  	}
	quicksort(array, M, 0, 0);

	for (i = 0; i < (M-1); i++) {
		if (pthread_create(&threadIds[i], NULL, threadFunction, NULL) != 0) {
			printf("Sort failed!\n");
			exit(1);
 		}
	n = 0; 
	while( M < 10000000) {
        if (M == n) {
            	for (i = 0; i < THREADS; i++) {
                	send_msg(
                    		send_msg_to_the_queue.begin_pos_msg,
                    		send_msg_to_the_queue.size,
                    		send_msg_to_the_queue.end_msg,1
                	);
            	}
            	break;
        }
  
	if (send_msg_to_the_queue.end_msg == 1) {
            n += send_msg_to_the_queue.size;
        }
	else {
            send_msg(
                send_msg_to_the_queue.begin_pos_msg,
                send_msg_to_the_queue.size,
                send_msg_to_the_queue.end_msg,
                send_msg_to_the_queue.end_pthread
            );
        }
    	}
	for(i = 0; i < THREADS; i++) {
        	pthread_join(threadIds[i], NULL);// this is blocking
    	}
	
	for (i = 0; i < (M-1); i++){
		if (array[i] > array[i+1]){
             		break;
         	}
    	}
    	while (queue_capacity > 0) {
        	receive_Msg();
    	}
    	pthread_mutex_destroy(&mutex);
    	pthread_cond_destroy(&msg_in);
    	pthread_cond_destroy(&msg_out);

  return 0;
}
