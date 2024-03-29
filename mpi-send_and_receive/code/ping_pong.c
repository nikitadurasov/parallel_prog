#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {

    const int PING_PONG_LIMIT = 10;
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size != 2) {
        fprintf(stderr, "World size must be 2 for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int ping_pong_count = 0;
    int partner_rank = (world_rank + 1) % 2;

    while (ping_pong_count < PING_PONG_LIMIT) {
        if (ping_pong_count % 2 == world_rank) {
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("SEND sender: %d - receiver: %d value %d\n", world_rank, partner_rank, ping_pong_count);
        } else {
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, 
                     MPI_STATUS_IGNORE);
            printf("RECV sender: %d -  receiver: %d value %d\n", partner_rank, world_rank, ping_pong_count);
        }
        ping_pong_count++;
    }

    MPI_Finalize();

}

