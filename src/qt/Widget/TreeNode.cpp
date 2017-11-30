/**
 * Tree node widget base
 */
#include <QtCore>
#include <QWidget>

#include <Resource/Icons.h>

#include "TreeNode.h"

using Orza::App::Resource::Icons;


namespace Orza { namespace App { namespace Widget {

/**
 * Events
 */

const char * TreeNode::DELETE_EVENT = "DELETE";
const char * TreeNode::VIEW_EVENT = "VIEW";


/**
 * Main methods
 */

void TreeNode::addNode( TreeNode * node ) {

    _nodes.add( node );

    Util::Event * e = new NodeRemoveEvent<TreeNode, TreeNode>( this );

    node->on( DELETE_EVENT, e );

};

void TreeNode::remove( TreeNode * node ) {

    _nodes.remove( node );

    delete node;

};


/**
 * Delete related
 */

void TreeNode::setDeleteButton( QPushButton * btn ) {

    delete_btn = btn;

    QFont iconFont = Icons::getFont( 20 );

    delete_btn->setFont( iconFont );
    delete_btn->setText( QChar( fa::trash ) );

    connect(
        delete_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handleRemoveClick() )
    );

};

void TreeNode::handleRemoveClick() {

    dispatch( DELETE_EVENT, this );

};


/**
 * View button setting
 */

void TreeNode::setViewButton( QPushButton * btn, QWidget * content ) {

    view_btn = btn;

    viewContent = content;

    QFont iconFont = Icons::getFont( 20 );

    view_btn->setFont( iconFont );
    view_btn->setText( QChar( fa::eye ) );

    connect(
        view_btn,
        SIGNAL( clicked() ),
        this,
        SLOT( handleViewClick() )
    );

};

void TreeNode::handleViewClick() {

    if( viewContent->isVisible() ) {

        viewContent->hide();

        view_btn->setStyleSheet( "color: #AAA" );

        view_btn->setText( QChar( fa::eyeslash ) );

    } else {

        viewContent->show();

        view_btn->setStyleSheet( "color: #FFF" );

        view_btn->setText( QChar( fa::eye ) );

    }

};

}; }; };
