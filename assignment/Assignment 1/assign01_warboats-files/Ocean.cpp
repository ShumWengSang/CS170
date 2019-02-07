/*!*****************************************************************************
\file   Ocean.cpp
\author Roland Shum
\par    email: roland.shum\@digipen.edu
\par    DigiPen Login: roland.shum 
\par    Course: CS170
\par    Section: A
\par    Assignment 1
\date   02/07/2019

\brief
    This file contains the implementation of the following functions for the 
    Warship assignment.
      
    Functions include:
    
       + CreateOcean
       + DestroyOcean
       + TakeShot
       + PlaceBoat
       + GetShotStates
       + DumpOcean
       
  Hours spent on this assignment: 5 hours.

  Specific portions that gave you the most trouble: Logic for placing boats.
  
*******************************************************************************/
// Boat, ShotStats, Point Orientation, ShotResult, BoatPlacement
#include "WarBoats.h" 
#include "Ocean.h"    // Ocean struct.
#include <iostream>   // cout, endl
#include <iomanip>    // setw

namespace CS170 //! namespace CS170
{
  namespace WarBoats //! namespace Warboats
  {
    const int BOAT_LENGTH = 4;  //!< Length of a boat
    const int HIT_OFFSET = 100; //!< Add this to the boat ID
    
    /*!*************************************************************************
      \fn static int& PointInOcean(Ocean &ocean, int x, int y)
      
      \brief
        Returns the int that represents that point in the grid in the given
        ocean, in the given x and y.
      
      \param ocean
        The ocean grid to check.
        
      \param x
        The x point in the grid.
        
      \param y
        The y point in the grid.
        
      \return 
        Returns the reference value in the grid at the given point.
    ***************************************************************************/
    static int& PointInOcean(Ocean &ocean, int x, int y)
    {
      return ocean.grid[y * ocean.x_quadrants + x];
    }
    
    /**************************************************************************/
    /*!
      \fn     static bool IsInOcean(int x, int y, Ocean *ocean)
      
      \brief
        Given an x and a y coordinate and an ocean, detects if the point is in 
        the ocean. There is an overloaded version of this function that takes 
        a struct Point.
      
      \param x
        The x point to check
        
      \param y
        The y point to check
      
      \param ocean
        The ocean to check with.
        
      \return 
        True if point is in ocean, false if it is outside.
    ***************************************************************************/
    static bool IsInOcean(int x, int y, Ocean *ocean)
    {
      if(0 > x || x >= ocean->x_quadrants)
        return false;
      if(0 > y || y >= ocean->y_quadrants)
        return false;
      return true;
    }
    
    /*!*************************************************************************
      \fn     static bool IsInOcean(Point point, Ocean *ocean)
      
      \brief
        Given a point and an ocean, detects if the point is in the ocean.
      
      \param point
        The x and y to check if point is in ocean.
      
      \param ocean
        The ocean to check with.
        
      \return 
        True if point is in ocean, false if it is outside.
    ***************************************************************************/
    static bool IsInOcean(Point point, Ocean *ocean)
    {
      return IsInOcean(point.x, point.y, ocean);
    }

    /*!*************************************************************************
      \fn    Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)
      
      \brief
        Creates the specified dimensions of the ocean and the number of
        boats that will be placed in it. An ocean will be dynamically allocated 
        and a pointer to it will be returned to the client.
      
      \param num_boats
        The number of boats in the ocean.
      
      \param x_quadrants
        How big on the x-axis the map is.
      
      \param y_quadrants
        How big on the y-axis the map is.
        
      \return 
        A pointer to the created 2D ocean.
    ***************************************************************************/
    Ocean *CreateOcean(int num_boats, int x_quadrants, int y_quadrants)
    {
      // Create a new Ocean, initialize to zero.
      Ocean *newOcean = new Ocean;
      
      // Create the 2D ocean, initialize to 0.
      newOcean->grid = new int [x_quadrants * y_quadrants]();
      
      // Create the boat array.
      newOcean->boats = new Boat [num_boats];
      
      // Check if new returned successfully
      if((newOcean == NULL) | (newOcean->grid == NULL) | 
         (newOcean->boats == NULL))
      {
        return NULL;
      }
      
      // Initialize the rest of the variables.
      newOcean->num_boats = num_boats;
      newOcean->x_quadrants = x_quadrants;
      newOcean->y_quadrants = y_quadrants;
      
      // Initialize garbage variables
      newOcean->stats.hits = 0;
      newOcean->stats.misses = 0;
      newOcean->stats.duplicates = 0;
      newOcean->stats.sunk = 0;
      
      // return ocean.
      return newOcean;
    }
    
    /*!*************************************************************************
      \fn     void DestroyOcean(Ocean *theOcean)
      
      \brief
         clean-up after the game. The function destroys an ocean that was 
         created using CreateOcean.
      
      \param theOcean
        Pointer to the Ocean to clean.       
    ***************************************************************************/
    void DestroyOcean(Ocean *theOcean)
    {
      // First clean up grid and boats.
      delete [] theOcean->grid;
      theOcean->grid = NULL;
      
      delete [] theOcean->boats;
      theOcean->boats = NULL;
      
      // Now we free the ocean itself.
      delete theOcean;
    }
    
    /*!*************************************************************************
      \fn     ShotResult TakeShot(Ocean &ocean, const Point &coordinate)
      
      \brief
         Client calls this in an attempt to hit one of the boats. 
         
         The coordinate parameter indicates where the client is attempting to
         strike. There are several possible results: Hit, Miss, Sunk, Duplicate,
         or Illegal. Hit, Miss, and Duplicate are obvious. Sunk is returned when
         a shot hits the last undamaged part of a boat. Sunk implies Hit.
         Illegal is any coordinate that is outside of the ocean (e.g. x or y '=
         less than 0 or outside the range).
      
      \param ocean
        The ocean to fire at.
        
      \param coordinate
        The coordinate to the user is trying to attack in the given ocean.
      
      \return
        The result of the shot. Can be any of the following:
        srHIT, srMISS, srDUPLICATE, srSUNK, srILLEGAL 
    ***************************************************************************/
    ShotResult TakeShot(Ocean &ocean, const Point &coordinate)
    {
      // If point is not in ocean.
      if(!IsInOcean(coordinate, &ocean))
      {
        // return illegal.
        return srILLEGAL;
      }
      // Get the point in ocean that was fired upon.
      int& value = PointInOcean(ocean, coordinate.x, coordinate.y);
      
      // If the shot is a miss.
      if(value == 0)
      {
        // Increment Misses.
        ocean.stats.misses++;
        
        // Set position to blown up.
        value = -1;
        
        //return miss shot result.
        return srMISS;
      }
      
      // A shot is a duplicate if its a hit, or a -1. A hit is above 100.
      if(value == -1 || value >= 100)
      {
        // Increment duplicates
        ocean.stats.duplicates++;
        
        // Return Duplicate shot result
        return srDUPLICATE;
      }
      
      // If we are here, we must have hit a boat. Increment hit.
      ocean.stats.hits++;
      
      // Bool to record of the boat has sunk.
      bool hasSunk = false;
      
      // Find the boat that was hit and increment it too. Value is ID.
      for(int i = 0; i < ocean.num_boats; i++)
      {
        // Find the boat with the corresponding ID.
        if(ocean.boats[i].ID == value)
        {
          // Increment the hits the boat has taken.
          ocean.boats[i].hits++;
          
          // If the boat is sinking, we record it and deal with it later.
          if(ocean.boats[i].hits >= BOAT_LENGTH)
          {
            hasSunk = true;
          }
          break;
        }
      }
      
      //Update position on ocean to boat hit
      value += 100;
      
      // Now we deal if the boat has sunk.
      if(hasSunk)
      {
        // Increment sunk
        ocean.stats.sunk++;
        
        // return Sunk shot result
        return srSUNK;
      }
      
      //  Return Hit shot result
      return srHIT;
    }
    
    /*!*************************************************************************
      \fn     BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)
      
      \brief
         Given an ocean and a boat, places the boat in the ocean.
         
         The client calls this to place boats in the ocean. The client will 
         create a boat and pass it to the function. The function must ensure 
         that the boat will "fit" in the ocean. Do this by checking the location
         where it is to be placed, the orientation (horizontal/vertical), and
         whether or not it will overlap with another boat or stick outside of 
         the ocean. The return value indicates whether or not the boat could be 
         placed in the ocean. See WarBoats.h for valid values of BoatPlacement.
      
      \param ocean
        The ocean to place the boat at.
        
      \param boat
        The boat which to place in the ocean.
        
      \return
        Whether the boat was successfully placed in the ocean. Can either be 
        bpACCEPTED, or bpREJECTED.
    ***************************************************************************/
    BoatPlacement PlaceBoat(Ocean &ocean, const Boat& boat)
    {
      // Check if the left/top of the boat is not in the ocean.     
      if(!IsInOcean(boat.position, &ocean))
      {
        // Reject the placement.
        return bpREJECTED;
      }
      
      // If boat is horizontal
      if(boat.orientation == oHORIZONTAL)
      {     
        // Check if right most position is not in map.
        if(!IsInOcean(boat.position.x + BOAT_LENGTH - 1, boat.position.y, 
           &ocean))
        {
          // Reject
           return bpREJECTED;
        }
      }
      // Boat is vertical.
      else
      {
        // Check the if bottom point is not in map.
        if(!IsInOcean(boat.position.x, boat.position.y + BOAT_LENGTH - 1, 
           &ocean))
        {
          // Reject
           return bpREJECTED;
        }
      }
      
      // Now check if the boats intersect with other boats.
      for (int i = 0; i < BOAT_LENGTH; i++)
      {
        int x = boat.position.x;   /* Easy way to get/set position x.*/
        int y = boat.position.y;   /* Easy way to get/set position y.*/

        // If orientation is horizontal, we need to i to go towards the right.
        if (boat.orientation == oHORIZONTAL)
          x += i;
        else // else if vertical, we need to i to go towards the bottom.     
          y += i;

        // If the point on the ocean is not empty.
        if (PointInOcean(ocean, x, y) != 0)
        {
          // Return reject.
          return bpREJECTED;
        }
      }

      // Now the place is clear to set the boat.
      for(int i = 0; i < BOAT_LENGTH; i++)
      {
        int x = boat.position.x;   /* Easy way to get/set position x.*/
        int y = boat.position.y;   /* Easy way to get/set position y.*/
        
        // If orientation is horizontal, we need to i to go towards the right.
        if(boat.orientation == oHORIZONTAL)
          x += i;
        else // else if vertical, we need to i to go towards the bottom.     
          y += i;
        
        // If the point on the ocean is empty.
        if(PointInOcean(ocean, x, y) == 0)
        {
          // Set the point on the map to the ID.
          PointInOcean(ocean, x, y) = boat.ID;
        }
      }
      static int index = 0; // Counter for boats array.

      // All went well, boat has been set. Add to array and retun accepted.
      ocean.boats[index] = boat;
      ocean.boats[index++].hits = 0; // Initialize the hit value if it isn't.
      return bpACCEPTED;
    }
    
    /*!*************************************************************************
      \fn     ShotStats GetShotStats(const Ocean &ocean)
      
      \brief
         Get the current statistics of the game, given the ocean.
      
      \param ocean
        The ocean to get the statistics.
        
      \return
        Returns a ShotStats struct that contains the number of hits, number of 
        misses, duplicates, and the amount of boats sunk.
        
        Internally, creates a copy of the ShotStats struct inside Ocean and 
        returns that.
    ***************************************************************************/
    ShotStats GetShotStats(const Ocean &ocean)
    {
      return ocean.stats;
    }


    /*!*************************************************************************
      \fn     void DumpOcean(const CS170::WarBoats::Ocean &ocean,
                                    int field_width, 
                                    bool extraline, 
                                    bool showboats)
      \brief
        Prints the grid (ocean) to the screen.
      
      \param ocean
        The Ocean to print
      
      \param field_width
        How much space each position takes when printed.
      
      \param extraline
        If true, an extra line is printed after each row. If false, no extra
        line is printed.
        
      \param showboats
        If true, the boats are shown in the output. (Debugging feature)
    ***************************************************************************/
    void DumpOcean(const CS170::WarBoats::Ocean &ocean,
                                    int field_width, 
                                    bool extraline, 
                                    bool showboats)
    {
        // For each row
      for (int y = 0; y < ocean.y_quadrants; y++)
      {
          // For each column
        for (int x = 0; x < ocean.x_quadrants; x++)
        {
             // Get value at x/y position
          int value = ocean.grid[y * ocean.x_quadrants + x];
    
            // Is it a boat that we need to keep hidden?
          if ( (value > 0) && (value < HIT_OFFSET) && (showboats == false) )
            value = 0;
    
          std::cout << std::setw(field_width) << value;
        }
        std::cout << std::endl;
        if (extraline)
          std::cout << std::endl;
      }
    }

  } // namespace WarBoats
} // namespace CS170
