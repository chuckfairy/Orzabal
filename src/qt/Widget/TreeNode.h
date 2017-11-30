/**
 * Tree node widget base
 */
#pragma once

#include <QtCore>
#include <QWidget>

#include <QPushButton>

#include <Util/Dispatcher.h>
#include <Util/Repository.h>

#include <Widget/Events/NodeRemoveEvent.h>

#include <Resource/Icons.h>


using Orza::App::Widget::NodeRemoveEvent;


namespace Orza { namespace App { namespace Widget {

class TreeNode : public QWidget, public Util::Dispatcher {

    Q_OBJECT;

    public:

        /**
         * Events
         */

        static const char * DELETE_EVENT;
        static const char * VIEW_EVENT;


        /**
         * Repo
         */

        void addNode( TreeNode * node );

        void remove( TreeNode * node );


        /**
         * View button setting
         */

        void setDeleteButton( QPushButton * );

        void setViewButton( QPushButton *, QWidget * );


        /**
         * Has methods
         */

        bool hasViewBtn() {

            return view_btn != nullptr;

        };

        bool hasDeleteBtn() {

            return delete_btn != nullptr;

        };


    public slots:

        void handleRemoveClick();

        void handleViewClick();


    protected:

        TreeNode() : QWidget() {};
        ~TreeNode() {};


    private:

        Util::Repository<TreeNode> _nodes;


        QPushButton * view_btn = nullptr;
        QPushButton * delete_btn = nullptr;

        QWidget * viewContent;

};

}; }; };
