#include "BO_VERWALTUNG.h"

BO* BO_VERWALTUNG::BOinstanz = 0;
BO_VERWALTUNG* BO_VERWALTUNG::VERWinstanz = 0;

BO_VERWALTUNG::BO_VERWALTUNG()
{
    modus_gesetzt=false;
    modus=0;
}

BO* BO_VERWALTUNG::holeInstanz()
{
  if( VERWinstanz == 0 )
  {
      VERWinstanz = new BO_VERWALTUNG();
  }
  if( BOinstanz == 0 )
  {
      if(VERWinstanz->modus==0) BOinstanz = new BO_KOM();
      if(VERWinstanz->modus==1) BOinstanz = new BO_GRA();
      else BOinstanz = new BO_KOM();//default BO_KOM
  }
  return BOinstanz;
}

void BO_VERWALTUNG::setzeModus(int tmpmodus)
{
    if( VERWinstanz == 0 )
    {
        VERWinstanz = new BO_VERWALTUNG();
    }
    if(!VERWinstanz->modus_gesetzt)
    {
        VERWinstanz->modus=tmpmodus;
        VERWinstanz->modus_gesetzt=true;
    }
}
