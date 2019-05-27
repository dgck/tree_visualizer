#ifndef QGVABSTRACTTREESCENEFACTORY_H
#define QGVABSTRACTTREESCENEFACTORY_H

#include "Trees/tree.h"
#include "QGVCore/QGVScene.h"
#include <QMainWindow>
#include "commons.h"
#include "Trees/binarytree.h"

#include <vector>
using std::vector;

/*!
 * \brief The QGVAbstractTreeSceneFactory class
 * Interface for all factories that return QGraphicsScene objects
 * This is needed for trees to render onto the screen
 */

class QGVAbstractTreeSceneFactory
{
public:
    QGVAbstractTreeSceneFactory(Tree* tree_ptr, QObject* parent_ptr = 0)
        :
          m_tree_ptr{tree_ptr},
          m_parent{parent_ptr}
    {
    }

    virtual ~QGVAbstractTreeSceneFactory()
    {

    }

    /*!
     * \brief construct_scene
     * \return
     * abstract method to manage construction of QGVScene
     */
    virtual QGVScene* construct_scene() = 0;

    /*!
     * \brief generate_traversal_scene
     * \return
     *
     * abstract method to manage construction of QGVScene objects when tree traversal is done
     */
    virtual QGVScene* generate_traversal_scene(Node* ) = 0;

    /*!
     * \brief get_scene
     * \return
     *
     * This is the interface that is supposed to be used by trees when they want to
     * record themselves
     */

    virtual QGVScene* generate_traversal_scene(vector <Node*> ) = 0;

    QGVScene* get_scene()
    {
        m_scene = construct_scene();
        m_scene -> applyLayout();

        //maybe do some building here before returning the pointer
        return m_scene;
    }

protected:
    Tree* m_tree_ptr;
    QGVScene* m_scene;
    QObject* m_parent;
};

#endif // QGVABSTRACTTREESCENEFACTORY_H
