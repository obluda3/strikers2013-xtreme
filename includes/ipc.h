struct IOVector {
  void *data;
  unsigned int size;
};

extern "C" {
int IOS_Open(const char *path, int mode);
int IOS_Close(int handle);
int IOS_Ioctlv(int handle, int command, int inputCount, int outputCount,
               IOVector *vec);
}