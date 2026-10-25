```
   ******   ******** **    ** ****     **   ******
  **////** **////// //**  ** /**/**   /**  **////**
 **    // /**        //****  /**//**  /** **    //
/**       /*********  //**   /** //** /**/**
/**       ////////**   /**   /**  //**/**/**
//**    **       /**   /**   /**   //****//**    **
 //******  ********    /**   /**    //*** //******
  //////  ////////     //    //      ///   //////
```

this is an alternative to syncthing and in general a personal project to help me learn c++ and just see how far i can get

the goal is a simple non-invasive P2P and low recource sync program 
fuck version control and backups at least for now I simply want file 1 to be identical to file 2... and room for expansion as it gets larger
to avoid scope creep this is a minimal program to begin with

# planned algorithm

## on change
- for each file changed store to changed.txt (or some lightweight format)
- generate a hash for each of the files modified
- update timestamp

## on sync
- compare dirsize, if they are identical then nothing has changed they are synced, otherwise:
- check timestamp for last change
- check changed.txt for what files have been modified
- if both folders have changed contents there is a conflict (i have not decided on a system for this yet)
- push updated files from the dir with the most up to date timestamp
- compare the hash of the downloaded files and source, if they are diffrent there was an error and try again, otherwise:
- update both timestamps to match, wipe both changed.txt, wipe the saved hashes


# To-Do
- [ ] merge functions to read timestamps and filesize into one multi-use function
- [ ] add file tracking
- [ ] sync files 
- [ ] cross-device support
- [ ] add lightweight deamon
- [ ] add support for syncing 3+ filesync
and a lot more but this is just a high level overview for what i have planned

# AI Disclaimer

This program has some light AI code, I am new to c++ and so it is a learning tool, i will comment whenever AI has been used

I try to solve a problem 3x with google before i resort to AI, i try to be conservative and use a local model when possible.