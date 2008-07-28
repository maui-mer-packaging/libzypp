/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/

#ifndef ZYPP_SOURCE_YUM_DOWNLOADER
#define ZYPP_SOURCE_YUM_DOWNLOADER

#include "zypp/Url.h"
#include "zypp/Pathname.h"
#include "zypp/Fetcher.h"
#include "zypp/OnMediaLocation.h"
#include "zypp/MediaSetAccess.h"
#include "zypp/ProgressData.h"
#include "zypp/RepoStatus.h"
#include "zypp/repo/Downloader.h"
#include "zypp/repo/yum/ResourceType.h"

namespace zypp
{
  namespace repo
  {
    namespace yum
    {
     /**
      * \short Downloader for YUM (rpm-nmd) repositories
      * Encapsulates all the knowledge of which files have
      * to be downloaded to the local disk.
      *
      * \code
      * MediaSetAccess media(url);
      * Downloader yum(path);
      * yum.download( media, "localdir");
      * \endcode
      */
      class Downloader : public repo::Downloader
      {
       public:
         
       /**
         * \short Constructor
         *
         * \param path Path to the repostory from the media
         */
        Downloader( const Pathname &path );
        
       /**
         * \short Download metadata to a local directory
         *
         * \param media Media access to the repository url
         * \param dest_dir Local destination directory
         * \param progress progress receiver
         */
        void download( MediaSetAccess &media,
                       const Pathname &dest_dir,
                       const ProgressData::ReceiverFnc & progress = ProgressData::ReceiverFnc() );
        
        /**
         * \short Status of the remote repository
         */
        RepoStatus status( MediaSetAccess &media );
        
       protected:
        bool repomd_Callback( const OnMediaLocation &loc, const ResourceType &dtype );
        bool patches_Callback( const OnMediaLocation &loc, const std::string &id );
       private:
        Pathname _path;
        Pathname _dest_dir;
        std::list<OnMediaLocation> _patches_files;
        
        MediaSetAccess *_media_ptr;
      };

    } // ns yum
  } // ns source
} // ns zypp

#endif