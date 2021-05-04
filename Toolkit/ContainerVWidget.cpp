#include "ContainerVWidget.h"

#include <iterator>


void ContainerVWidget::addconstraint( int value, char *type )
{
    constraintvalue.push_back(value);
    constrainttype.push_back(type);
}


void ContainerVWidget::adjust( )
{
    if (parent)
    {
        if ((strcmp( parent->getwidgettype(),(char*) "ContainerV" )==0) || (strcmp( parent->getwidgettype(),(char*) "ContainerH" )==0))
        {
            // nothing to do, it comes from the parent
        }
        else
        {
            xpos = parent->getuseablexpos();
            ypos = parent->getuseableypos();
            width = parent->getuseablewidth();
            height = parent->getuseableheight();
        }
    }

    // If no constraint have been defined, then we just divide the size by the number of children
    if ((constraintvalue.size()==0) || (constrainttype.size()==0))
    {
        int i=0;
        nbchildren = children.size();

        for (auto& c : children )
        {
            c->setdimensions( xpos, ypos+1 + height/nbchildren*i, width, height/nbchildren-2 );
            i++;
        }
    }
    else
    {

        if ((constraintvalue.size() == constrainttype.size()) && (constraintvalue.size() == children.size()))
        {
            unsigned int remainingheight = this->height;
            // first loop based on direct assignement of size by constraint in pixels
            auto it1 = constraintvalue.begin();
            auto it2 = constrainttype.begin();
            auto it3 = children.begin();

            for (unsigned int temp=0; temp<children.size(); temp++)
            {
                // if the constraint is an absolute pixel value, we directly report the value as the dimension that is needed
                if (strcmp(*it2, "px")==0)
                {
                    // We have the information for width (imposed by constraint), ypos and height are coming from available space useable
                    (*it3)->setwidth( width-2 );
                    (*it3)->setheight( *it1-2 );
                    (*it3)->setxpos( xpos+1 );
                    // for ypos, we will have to compute when everything else will be computed later on

                    // before going to percentage constraint, we will have to compute the remaining space to be split by percentages
                    remainingheight -= ( *it1 );
                }

                it1++;
                it2++;
                it3++;
            }


            // second loop based on assignement of percentages of remaining space

            it1 = constraintvalue.begin();
            it2 = constrainttype.begin();
            it3 = children.begin();

            for (unsigned int temp=0; temp<children.size(); temp++)
            {
                // if the constraint is an absolute pixel value, we directly report the value as the dimension that is needed
                if (strcmp(*it2, "%")==0)
                {
                    // We have the information for width (imposed by constraint), xpos and height are coming from available space useable
                    (*it3)->setwidth( width -2 );
                    (*it3)->setheight(  (unsigned int) (*it1 * remainingheight / 100 -2)  );
                    (*it3)->setxpos( xpos +1);
                    // for ypos, we will have to compute when everything else will be computed later on
                }

                it1++;
                it2++;
                it3++;
            }

            // No we compute the remaining dimension (xpos)
            unsigned int currenty = ypos + 1;
            for( auto it=children.begin(); it!=children.end(); it++ )
            {
                (*it)->setypos( currenty );
                currenty += (*it)->getheight() +2;
            }

        }

    }

    for (auto& c : children )
        c->adjust();
}

void ContainerVWidget::logic( CursorTask *mouse, KeyboardTask *keyboard )
{
    if (is_enabled && is_visible)
    {
        for (auto& c : children )
            c->logic( mouse, keyboard );
    }
}

void ContainerVWidget::render( SDL_Surface *screen, ColorEngine *colors, FontEngine *fonts )
{
    if (is_visible)
    {
        for (auto& c : children )
            c->render( screen, colors, fonts );
    }
}
