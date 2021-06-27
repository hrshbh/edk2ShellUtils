/** @file
  Main file for NULL named library for level 3 shell command functions.

  (C) Copyright 2014 Hewlett-Packard Development Company, L.P.<BR>
  Copyright (c) 2009 - 2011, Intel Corporation. All rights reserved. <BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

  Modified By: Hrishabh Rajput
**/
#include "UefiShellLevelXCommandsLib.h"

CONST CHAR16 gShellLevelXFileName[] = L"ShellCommands";
EFI_HII_HANDLE gShellLevelXHiiHandle = NULL;

/**
  return the filename to get help from is not using HII.

  @retval The filename.
**/
CONST CHAR16*
EFIAPI
ShellCommandGetManFileNameLevelX (
  VOID
  )
{
  return (gShellLevelXFileName);
}

/**
  Constructor for the Shell Level X Commands library.

  Install the handlers for level X UEFI Shell 2.0 commands.

  @param ImageHandle    the image handle of the process
  @param SystemTable    the EFI System Table pointer

  @retval EFI_SUCCESS        the shell command handlers were installed sucessfully
  @retval EFI_UNSUPPORTED    the shell level required was not found.
**/
EFI_STATUS
EFIAPI
ShellLevelXCommandsLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  gShellLevelXHiiHandle = NULL;
  //
  // if shell level is less than 3 do nothing
  //
  if (PcdGet8(PcdShellSupportLevel) < 3) {
    return (EFI_SUCCESS);
  }

  gShellLevelXHiiHandle = HiiAddPackages (&gShellLevelXHiiGuid, gImageHandle, UefiShellLevelXCommandsLibStrings, NULL);
  if (gShellLevelXHiiHandle == NULL) {
    return (EFI_DEVICE_ERROR);
  }
  //
  // install our shell command handlers that are always installed
  //
  // Note: that Time, Timezone, and Date are part of level 2 library
  //
  ShellCommandRegisterCommandName(L"head",    ShellCommandRunHead   , ShellCommandGetManFileNameLevelX, 3, L"", TRUE , gShellLevelXHiiHandle, STRING_TOKEN(STR_GET_HELP_HEAD));

  return (EFI_SUCCESS);
}

/**
  Destructor for the library.  free any resources.

  @param ImageHandle            The image handle of the process.
  @param SystemTable            The EFI System Table pointer.
**/
EFI_STATUS
EFIAPI
ShellLevelXCommandsLibDestructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  if (gShellLevelXHiiHandle != NULL) {
    HiiRemovePackages(gShellLevelXHiiHandle);
  }
  return (EFI_SUCCESS);
}
