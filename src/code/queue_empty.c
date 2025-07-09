struct queue* empty_queue ()
/*@ ensures take ret = QueuePtr_At(return);
            ret == Nil{}; @*/
{
  struct queue *p = malloc_queue();
  p->front = NULL;
  p->back = NULL;
  return p;
}
