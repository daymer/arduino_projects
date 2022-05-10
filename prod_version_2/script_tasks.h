struct StepTask {
  unsigned long i; //target step
  unsigned long n; //how many times to rep
  int m; //on which n to start a default length step
};

struct DirTask {
  unsigned long i; //target step
  bool d; //which dir to go
}; 
