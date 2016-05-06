#include "../header/hardware_fifo.h"

HardwareFifo* fifo_constructor(uint size, uint num_fifos, uint num_buffers, uint blk_size)
{
	HardwareFifo* fifo = (HardwareFifo*)malloc(sizeof(HardwareFifo));
	fifo->size = size;
	fifo->num_fifos = num_fifos;
	fifo->num_buffers =  num_buffers;
	fifo->blk_size = blk_size;

	fifo->buffers = (CircularBuffer**)malloc(sizeof(CircularBuffer*));

	int i;
	for(i=0; i<num_buffers; i++)
	{
		fifo->buffers[i] = buffer_constructor(fifo->blk_size);
	}

	fifo->fifos = (List**)malloc(sizeof(List*));

	for(i=0; i<num_fifos; i++)
	{
		fifo->fifos[i] = list_constructor();
	}
}

uint fifo_push(uint id, TYPE value, HardwareFifo* fifo)
{
}

uint fifo_pop(uint id, HardwareFifo* fifo)
{
}

TYPE fifo_top(uint id, HardwareFifo* fifo)
{
}
