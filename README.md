# CrossQFile

A QFile that supports Android Uri.

QFile was supposed to be a cross-platform file processing class. although you can work with QFile in android, but you can not work with all files using QFile. To work with all files in the storage, you must use Android Uris. QFile does not support Android Uris.

CrossQFile is a QFile that supports Android Uris. so you can use it to work with android files. all of added features all completely transparent to other platforms.


## How to use

Just add CrossQFile.h and CrossQFile.cpp to your project. now you can use CrossQFile as a usual QFile. When you want to open a file with Android Uri, just pass the UriString to the CrossQFile constructor
 and set the second arguemnt to true.

 Example:
```
   ...
   CrossQFile file {uriString, true};
   ...
```


 ### Sample Code
 You can clone this project and build it both for Windows and Android. the main function of project is a sample code for how to use CrossQFile.