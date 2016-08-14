struct file {
  enum { FD_NONE, FD_PIPE, FD_INODE } type;
  int ref; // reference count
  char readable;
  char writable;
  struct pipe *pipe;
  struct inode *ip;
  uint off;
};


// in-memory copy of an inode
struct inode {
  uint dev;           // Device number
  uint inum;          // Inode number
  int ref;            // Reference count
  int flags;          // I_BUSY, I_VALID

  short type;         // copy of disk inode
  short major;
  short minor;
  short nlink;
  uint size;
  int mtime;
  uint addrs[NDIRECT+1];
};
#define I_BUSY 0x1
#define I_VALID 0x2

// table mapping major device number to
// device functions
struct devsw {
  int (*read)(struct inode*, char*, uint, int);
  int (*write)(struct inode*, char*, uint, int);
  int (*ioctl)(struct inode*, int);
};

extern struct devsw devsw[];

#define CONSOLE 1	// /dev/console, /dev/serial
#define DISK    2	// /dev/disk0,   /dev/disk1
#define DEVNULL 3	// /dev/null,    /dev/zero

// lseek defines
#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

//PAGEBREAK!
// Blank page.
