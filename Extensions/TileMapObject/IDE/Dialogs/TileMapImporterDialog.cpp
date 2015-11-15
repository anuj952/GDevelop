#include "TileMapImporterDialog.h"

#if defined(GD_IDE_ONLY) && !defined(GD_NO_WX_GUI)
#include "IDE/TMXImport/TileMapImporter.h"
#include "TileSet.h"
#include "TileMap.h"

TileMapImporterDialog::TileMapImporterDialog(wxWindow* parent, TileSet tileset, TileMap tilemap, gd::ResourcesManager &resManager)
    : TileMapImporterDialogBase(parent),
    m_tileset(tileset),
    m_tilemap(tilemap),
    m_resManager(resManager)
{
    m_okBt->Disable();
}

TileMapImporterDialog::~TileMapImporterDialog()
{
}

void TileMapImporterDialog::OnBrowserBtClicked(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Import .tmx file"), "", "", "Tiled file (*.tmx)|*.tmx", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    m_fileTextCtrl->SetValue(openFileDialog.GetPath());
}

void TileMapImporterDialog::OnImportButtonClicked(wxCommandEvent& event)
{
    try
    {
        m_okBt->Enable();
        wxString errorStr;
        TileMapImporter importer(m_fileTextCtrl->GetValue(), errorStr);

        //TODO: Check the checkboxes :) !
        if(!importer.ImportTileMap(m_tileset, m_tilemap,
            m_importOptionsCheckList->IsChecked(0),
            m_importOptionsCheckList->IsChecked(1),
            m_importOptionsCheckList->IsChecked(2),
            m_importOptionsCheckList->IsChecked(3),
            m_resManager))
        {
            m_okBt->Disable();
        }

        m_problemsTextCtrl->SetValue(errorStr);
    }
    catch (const std::runtime_error &exc)
    {
        m_problemsTextCtrl->SetValue(_("ERROR: Unable to read the file"));
        m_okBt->Disable();
    }
}

void TileMapImporterDialog::OnOkBtClicked(wxCommandEvent& event)
{
    EndModal(1);
}

void TileMapImporterDialog::OnCancelBtClicked(wxCommandEvent& event)
{
    EndModal(0);
}

#endif
