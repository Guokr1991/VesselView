/*=========================================================================

Library:   VesselView

Copyright 2010 Kitware Inc. 28 Corporate Drive,
Clifton Park, NY, 12065, USA.

All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=========================================================================*/

// Qt includes
#include <QDebug>
#include <QtPlugin>

// Slicer includes
#include <qSlicerCoreApplication.h>
#include <qSlicerModuleManager.h>

// Logic includes
#include <vtkSlicerCLIModuleLogic.h>
#include "vtkSlicerSpatialObjectsLogic.h"
#include <vtkSlicerInteractiveTubesToTreeLogic.h>

// InteractiveTubesToTree includes
#include "qSlicerInteractiveTubesToTreeModule.h"
#include "qSlicerInteractiveTubesToTreeModuleWidget.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2
  ( qSlicerInteractiveTubesToTreeModule, qSlicerInteractiveTubesToTreeModule );

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerInteractiveTubesToTreeModulePrivate
{
public:
  qSlicerInteractiveTubesToTreeModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerInteractiveTubesToTreeModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerInteractiveTubesToTreeModulePrivate::qSlicerInteractiveTubesToTreeModulePrivate()
{
}

//-----------------------------------------------------------------------------
//qSlicerInteractiveTubesToTreeModule methods

//-----------------------------------------------------------------------------
qSlicerInteractiveTubesToTreeModule::qSlicerInteractiveTubesToTreeModule
  ( QObject* _parent ) : Superclass( _parent ),
  d_ptr( new qSlicerInteractiveTubesToTreeModulePrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerInteractiveTubesToTreeModule::~qSlicerInteractiveTubesToTreeModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerInteractiveTubesToTreeModule::helpText() const
{
  return "This module helps user to interactively build Tube-Tree from tubes,"
    " i.e assign a parent child relationship to the tubes.";
}

//-----------------------------------------------------------------------------
QString qSlicerInteractiveTubesToTreeModule::acknowledgementText() const
{
  return "This work is part of the VesselView project at Kitware.";
}

//-----------------------------------------------------------------------------
QStringList qSlicerInteractiveTubesToTreeModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString( "Sumedha Singla (Kitware Inc)" );
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerInteractiveTubesToTreeModule::icon() const
{
  return QIcon( ":/Icons/InteractiveTubesToTree.png" );
}

//-----------------------------------------------------------------------------
QStringList qSlicerInteractiveTubesToTreeModule::categories() const
{
  return QStringList() << "TubeTK";
}

//-----------------------------------------------------------------------------
QStringList qSlicerInteractiveTubesToTreeModule::dependencies() const
{
  QStringList moduleDependencies;
  moduleDependencies << "SpatialObjects";
  moduleDependencies << "ConvertTubesToTubeTree";

  return moduleDependencies;
}

//-----------------------------------------------------------------------------
void qSlicerInteractiveTubesToTreeModule::setup()
{
  this->Superclass::setup();
  vtkSlicerInteractiveTubesToTreeLogic* interactiveTubeToTreeLogic =
    vtkSlicerInteractiveTubesToTreeLogic::SafeDownCast( this->logic() );

  qSlicerAbstractCoreModule* conversionModule =
    qSlicerCoreApplication::application()->moduleManager()->module
    ( "ConvertTubesToTubeTree" );

  qSlicerAbstractCoreModule* spatialObjectsModule =
    qSlicerCoreApplication::application()->moduleManager()->module( "SpatialObjects" );

  if ( conversionModule  && spatialObjectsModule )
    {
    vtkSlicerCLIModuleLogic* conversionLogic =
      vtkSlicerCLIModuleLogic::SafeDownCast( conversionModule->logic() );
    interactiveTubeToTreeLogic->SetConversionLogic( conversionLogic );

    vtkSlicerSpatialObjectsLogic* spatialObjectsLogic =
      vtkSlicerSpatialObjectsLogic::SafeDownCast( spatialObjectsModule->logic() );
    interactiveTubeToTreeLogic->SetSpatialObjectsLogic( spatialObjectsLogic );

    qWarning() << "ConvertTubesToTubeTree module is found";
    }
  else
    {
    qWarning() << "ConvertTubesToTubeTree module is not found";
    }
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerInteractiveTubesToTreeModule
::createWidgetRepresentation()
{
  return new qSlicerInteractiveTubesToTreeModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerInteractiveTubesToTreeModule::createLogic()
{
  return vtkSlicerInteractiveTubesToTreeLogic::New();
}
